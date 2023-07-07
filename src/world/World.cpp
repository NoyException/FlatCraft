//
// Created by Noy on 2023/7/3.
//


#include <utility>

#include "world/World.h"

World::World(const std::string& name) : name_(std::move(name)) {
    init();
}

std::string World::getName() const {
    return name_;
}

Block* World::getBlock(int x, int y, bool front) const {
    auto it = blocks_.find((x<<11)^(y<<1)^front);
    if(it==blocks_.end()) return {};
    return it->second.get();
}

Block* World::getBlock(const Location &location, bool front) const {
    if(location.getRawWorld()!=name_) return nullptr;
    return getBlock(location.getBlockX(), location.getBlockY(), front);
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
            int hash = (i<<11)^(j<<1);
            Material m;
            if(j==0) m = Material::BED_ROCK;
            else if(j<48) m = Material::STONE;
            else if(j<64) m = Material::DIRT;
            else if(j==64) m = Material::GRASS;
            else m = Material::AIR;
            blocks_[hash] = std::make_unique<Block>(m,Location(name_,i,j),false);
            blocks_[hash^1] = std::make_unique<Block>(m,Location(name_,i,j),true);
        }
    }
}

nlohmann::json World::serialize() const {
    nlohmann::json json({{"name",name_}});
    nlohmann::json blocks;
    for(int i=-128;i<=128;i++) {
        for (int j = 0; j < 256; j++) {
            for(int k = 0; k <= 1; k++){
                std::stringstream ss;
                ss<<i<<"_"<<j<<"_"<<k;
                blocks.emplace(ss.str(), getBlock(i,j,k)->serialize());
            }
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
            for(int k = 0; k <= 1; k++) {
                std::stringstream ss;
                ss << i << "_" << j << "_" << k;
                Block block = Block::deserialize(Location(world.name_, i, j),
                                                 k,blocks.at(ss.str()));
                int hash = (i << 11) ^ (j << 1) ^ k;
                world.blocks_[hash] = std::make_unique<Block>(block);
            }
        }
    }
    return std::move(world);
}

std::unique_ptr<RayTraceResult> World::rayTrace(const Location &location, const Vec2d &direction,
                                                double maxDistance, double raySize,
                                                const std::function<bool(Material)>& blockFilter,
                                                const std::function<bool(Entity *)>& entityFilter) const {
    for (auto &item: entities_){
        if(entityFilter(item)){

        }
    }
    return nullptr;
}

