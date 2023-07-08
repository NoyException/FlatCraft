//
// Created by Noy on 2023/7/3.
//

#include "entity/Entity.h"
#include "world/World.h"
#include "FlatCraft.h"
#include "event/instance/EntityTeleportEvent.h"

Entity::Entity(const Location &spawnLocation) : location_(spawnLocation), velocity_(), boundingBox_(0,0,0,0){
    physicsTask_ = FlatCraft::getInstance()->getScheduler()->runTaskTimer([&]() {
        if (!isOnGround()) {
            velocity_.add(0, -0.02);
        }
        move();
    },0,0);
}

Entity::~Entity() {
    physicsTask_->cancel();
}

Location Entity::getLocation() const {
    return location_;
}

World *Entity::getWorld() const {
    return location_.getWorld();
}

void Entity::teleport(const Location &location) {
    EntityTeleportEvent event(this, location);
    EventManager::callEvent(event);
    if(event.isCanceled()) return;
    Location targetLocation = event.getTargetLocation();
    World* oldWorld = targetLocation.getWorld();
    location_ = targetLocation;
    if(targetLocation.getWorld()!=oldWorld){
        if(oldWorld != nullptr) oldWorld->notifyTeleported(*this);
        targetLocation.getWorld()->notifyTeleported(*this);
    }
}

void Entity::move() {
    move(velocity_);
}

void Entity::move(const Vec2d &dv) {
//    getWorld()->rayTrace(location_,dv,256,)
    location_.add(dv);
}

nlohmann::json Entity::serialize() const {
    return {{"location",location_.serialize()}};
}

bool Entity::isOnGround() const {
    Block* block = location_.getBlock(true);
    if(block == nullptr) return false;
    return MaterialHelper::isOccluded(block->getMaterial()) && (location_.getY()-location_.getBlockY())==0.0;
}

Vec2d Entity::getVelocity() const {
    return velocity_;
}

BoundingBox Entity::getBoundingBox() const {
    return boundingBox_;
}

