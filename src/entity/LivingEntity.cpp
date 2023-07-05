//
// Created by Noy on 2023/7/3.
//

#include "entity/LivingEntity.h"

LivingEntity::LivingEntity(const Location &spawnLocation) : Entity(spawnLocation) {
}

bool LivingEntity::isDead() const {
    return health_<=0;
}

nlohmann::json LivingEntity::serialize() const {
    nlohmann::json &&j = Entity::serialize();
    j.merge_patch(nlohmann::json{{"health",health_}});
    return j;
}

double LivingEntity::getHealth() const {
    return health_;
}

void LivingEntity::setHealth(double health) {
    health_ = health;
}