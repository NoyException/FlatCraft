//
// Created by Noy on 2023/7/3.
//

#include "entity/Entity.h"
#include "world/World.h"

Location Entity::getLocation() const {
    return location_;
}

void Entity::teleport(const Location &location) {
    location_ = location;
    location.getWorld()->notifyTeleported(*this);
}

Entity::Entity(const Location &spawnLocation) : location_(spawnLocation){}

nlohmann::json Entity::serialize() const {
    return nlohmann::json{
            {"location",location_.serialize()}
    };
}

