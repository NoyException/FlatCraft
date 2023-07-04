//
// Created by Noy on 2023/7/3.
//

#include "entity/LivingEntity.h"

LivingEntity::LivingEntity(const Location &spawnLocation) : Entity(spawnLocation) {
}

bool LivingEntity::isDead() const {
    return health_<=0;
}
