//
// Created by Noy on 2023/7/3.
//

#include "entity/Entity.h"
#include "world/World.h"

Location Entity::getLocation() const {
    return location_;
}

void Entity::teleport(const Location &location) {
    World* oldWorld = location.getWorld();
    location_ = location;
    if(oldWorld != nullptr) oldWorld->notifyTeleported(*this);
    location.getWorld()->notifyTeleported(*this);
}

Entity::Entity(const Location &spawnLocation) : location_(spawnLocation){}

nlohmann::json Entity::serialize() const {
    return {{"location",location_.serialize()}};
}

