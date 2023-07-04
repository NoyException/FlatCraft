//
// Created by Noy on 2023/7/3.
//


#include <utility>

#include "world/World.h"

World::World(std::string name) : name_(std::move(name)) {

}

std::string World::getName() const {
    return name_;
}

Block* World::getBlock(int x, int y) const {
    auto it = blocks_.find((x<<10)^y);
    if(it==blocks_.end()) return {};
    return it->second.get();
}

Block* World::getBlock(const Location &location) const {
    return getBlock(location.getBlockX(), location.getBlockY());
}

void World::notifyTeleported(Entity &entity) {
    if(entity.getLocation().getWorld()==this)
        entities_.insert(&entity);
    else
        entities_.erase(&entity);
}

void World::getEntities(std::vector<Entity*> &entities) const {
    for (const auto &item: entities_){
        entities.push_back(item);
    }
}

void World::getEntities(std::vector<Entity*> &entities, bool (*filter)(const Entity &)) const {
    for (const auto &item: entities_){
        if(filter(*item)) entities.push_back(item);
    }
}

void World::init() {
    for(int i=-128;i<=128;i++){
        for(int j=0;j<256;j++){
            int hash = (i<<10)^j;
            blocks_[hash] = std::make_unique<Block>(Material::AIR,Location(name_,i,j));
        }
    }
}
