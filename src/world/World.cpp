//
// Created by Noy on 2023/7/3.
//


#include <utility>

#include "world/World.h"

World::World(std::string name) : name_(std::move(name)) {
    init();
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
    if(entity.getLocation().getRawWorld()==name_)
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
            Material m;
            if(j==0) m = Material::BED_ROCK;
            else if(j<48) m = Material::STONE;
            else if(j<64) m = Material::DIRT;
            else if(j==64) m = Material::GRASS;
            else m = Material::AIR;
            blocks_[hash] = std::make_unique<Block>(m,Location(name_,i,j));
        }
    }
}

nlohmann::json World::serialize() const {
    nlohmann::json json({{"name",name_}});
    nlohmann::json blocks;
    for(int i=-128;i<=128;i++) {
        for (int j = 0; j < 256; j++) {
            std::stringstream ss;
            ss<<i<<"_"<<j;
            blocks.emplace(ss.str(), getBlock(i,j)->serialize());
        }
    }
    json.emplace("blocks",std::move(blocks));
    return std::move(json);
}

World World::deserialize(const nlohmann::json &json) {
    World world(json.at("name").get<std::string>());
    auto blocks = json.at("blocks");
    for(int i=-128;i<=128;i++) {
        for (int j = 0; j < 256; j++) {
            std::stringstream ss;
            ss<<i<<"_"<<j;
            Block block = Block::deserialize(Location(world.name_,i,j),
                                               blocks.at(ss.str()));
            int hash = (i<<10)^j;
            world.blocks_[hash] = std::make_unique<Block>(block);
        }
    }
    return std::move(world);
}
