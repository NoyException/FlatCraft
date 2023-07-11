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

class World {
public:
    friend class Entity;
    friend class WorldGenerator;
    explicit World(const std::string& name);
    [[nodiscard]] nlohmann::json serialize() const;
    static World deserialize(const nlohmann::json& json);
    void run();
    void stop();
    [[nodiscard]] bool isRunning() const;
    [[nodiscard]] long long getTicks() const;
    [[nodiscard]] Weather getWeather() const;
    void setWeather(Weather weather);
    [[nodiscard]] std::string getName() const;
    void getEntities(std::vector<Entity*>& entities) const;
    void getEntities(std::vector<Entity*>& entities, bool(*filter)(const Entity&)) const;
    [[nodiscard]] Block* getBlock(int x, int y, bool front) const;
    [[nodiscard]] Block* getBlock(const Vec2d& v, bool front) const;
    [[nodiscard]] Block* getBlock(const Location& location, bool front) const;
    std::unique_ptr<RayTraceResult> rayTrace(const Vec2d& startPoint, const Vec2d& direction,
                                             double maxDistance, double xSize, double ySize, bool hitBackground = false,
                                             const std::function<bool(Block*)>& blockFilter = [](Block* block){return MaterialHelper::isOccluded(block->getMaterial());},
                                             const std::function<bool(Entity*)>& entityFilter = [](Entity*){return false;}) const;
    std::unique_ptr<RayTraceResult> rayTrace(const Location& location, const Vec2d& direction,
                                             double maxDistance, double xSize, double ySize, bool hitBackground,
                                             const std::function<bool(Block*)>& blockFilter,
                                             const std::function<bool(Entity*)>& entityFilter) const;
private:
    void init();
    void notifyTeleported(Entity& entity);
    void setBlock(int x, int y, bool front, Material material);
    Task* task_ = nullptr;
    long long ticks_;
    Weather weather_;
    Random rand_{};
    std::string name_;
    std::set<Entity*> entities_;
    std::unordered_map<int, std::unique_ptr<Block>> blocks_;
};


#endif //FLATCRAFT_WORLD_H
