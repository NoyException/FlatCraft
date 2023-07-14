//
// Created by Noy on 2023/7/3.
//

#ifndef FLATCRAFT_WORLD_H
#define FLATCRAFT_WORLD_H

#include "common.h"
#include "Block.h"
#include "model/entity/Entity.h"
#include "RayTraceResult.h"
#include "model/event/events.h"

class ItemStack;

class World {
public:
    friend class Entity;
    friend class WorldGenerator;
    World(const std::string& name, long long seed);
    explicit World(const nlohmann::json& json);
    [[nodiscard]] std::unique_ptr<nlohmann::json> serialize() const;
    static std::unique_ptr<World> deserialize(const nlohmann::json& json);
    void run();
    void stop();
    [[nodiscard]] bool isRunning() const;
    [[nodiscard]] long long getSeed() const;
    [[nodiscard]] long long getTicks() const;
    [[nodiscard]] Weather getWeather() const;
    void setWeather(Weather weather);
    [[nodiscard]] std::string getName() const;
    void getEntities(std::vector<Entity*>& entities) const;
    void getEntities(std::vector<Entity*>& entities, const std::function<bool(const Entity&)>& filter) const;
    void getEntitiesNearby(std::vector<Entity*>& entities, const Vec2d& position, double r,
                           const std::function<bool(const Entity&)>& filter=[](const Entity&){return true;}) const;
    template<class E>
    void getEntitiesNearby(std::vector<E*>& entities, const Vec2d& position, double r,
                           const std::function<bool(const E&)>& filter=[](E&){return true;}) const;
    [[nodiscard]] Block* getBlock(int x, int y, bool front) const;
    [[nodiscard]] Block* getBlock(const Vec2d& v, bool front) const;
    [[nodiscard]] Block* getBlock(const Location& location, bool front) const;
    void dropItem(const Vec2d& position, std::unique_ptr<ItemStack>&& itemStack);
    std::unique_ptr<RayTraceResult> rayTrace(const Vec2d& startPoint, const Vec2d& direction,
                                             double maxDistance, double xSize, double ySize, bool hitBackground = false,
                                             const std::function<bool(const Block*)>& blockFilter = [](const Block* block){return MaterialHelper::isOccluded(block->getMaterial());},
                                             const std::function<bool(const Entity*)>& entityFilter = [](const Entity*){return false;}) const;
    std::unique_ptr<RayTraceResult> rayTrace(const Location& location, const Vec2d& direction,
                                             double maxDistance, double xSize, double ySize, bool hitBackground,
                                             const std::function<bool(const Block*)>& blockFilter,
                                             const std::function<bool(const Entity*)>& entityFilter) const;

private:
    void init();
    void notifyEntityJoin(Entity* entity);
    void notifyEntityLeave(Entity* entity);
    void setBlock(int x, int y, bool front, Material material);
    bool validate() const;
    std::shared_ptr<Task> task_ = nullptr;
    long long seed_;
    long long ticks_;
    Weather weather_;
    Random rand_;
    std::string name_;
    std::set<Entity*> entities_;
    std::unordered_map<int, std::unique_ptr<Block>> blocks_;
};

template<class E>
void World::getEntitiesNearby(std::vector<E*>& entities, const Vec2d& position, double r,
                       const std::function<bool(const E&)>& filter) const{
    std::vector<Entity*> tmp;
    getEntitiesNearby(tmp, position, r, [&](const Entity& entity){
        const E* e = dynamic_cast<const E*>(&entity);
        return e!=nullptr && filter(*e);
    });
    for (auto &item: tmp){
        entities.push_back(dynamic_cast<E*>(item));
    }
}

#endif //FLATCRAFT_WORLD_H
