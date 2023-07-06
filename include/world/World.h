//
// Created by Noy on 2023/7/3.
//

#ifndef FLATCRAFT_WORLD_H
#define FLATCRAFT_WORLD_H

#include <common.h>
#include "Block.h"
#include "entity/Entity.h"
#include "Location.h"

class World {
public:
    friend class Entity;
    explicit World(std::string name);
    [[nodiscard]] nlohmann::json serialize() const;
    static World deserialize(const nlohmann::json& json);
    [[nodiscard]] std::string getName() const;
    void getEntities(std::vector<Entity*>& entities) const;
    void getEntities(std::vector<Entity*>& entities, bool(*filter)(const Entity&)) const;
    [[nodiscard]] Block* getBlock(int x, int y, bool front) const;
    [[nodiscard]] Block* getBlock(const Location& location, bool front) const;
private:
    void init();
    void notifyTeleported(Entity& entity);
    std::string name_;
    std::set<Entity*> entities_;
    std::unordered_map<int, std::unique_ptr<Block>> blocks_;
};


#endif //FLATCRAFT_WORLD_H
