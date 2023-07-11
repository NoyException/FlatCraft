//
// Created by Noy on 2023/7/3.
//

#include "model/entity/LivingEntity.h"

LivingEntity::LivingEntity(const Location &spawnLocation) : Entity(spawnLocation), health_(20) {
}

LivingEntity::LivingEntity(const nlohmann::json &json) : Entity(json),
health_(json.at("health").get<double>()) {}

std::unique_ptr<nlohmann::json> LivingEntity::serialize() const {
    std::unique_ptr<nlohmann::json> j = Entity::serialize();
    j->merge_patch(nlohmann::json{{"health",health_}});
    return j;
}

bool LivingEntity::isDead() const {
    return health_<=0;
}

double LivingEntity::getHealth() const {
    return health_;
}

void LivingEntity::setHealth(double health) {
    health_ = health;
}
