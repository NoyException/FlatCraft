//
// Created by Noy on 2023/7/3.
//

#include "entity/Entity.h"
#include "world/World.h"
#include "FlatCraft.h"

Entity::Entity(const Location &spawnLocation) : location_(spawnLocation), velocity_(){
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
    World* oldWorld = location.getWorld();
    location_ = location;
    if(oldWorld != nullptr) oldWorld->notifyTeleported(*this);
    location.getWorld()->notifyTeleported(*this);
}

void Entity::move() {
    move(velocity_);
}

void Entity::move(const Vec2d &dv) {

}

nlohmann::json Entity::serialize() const {
    return {{"location",location_.serialize()}};
}

bool Entity::isOnGround() const {
    Block* block = location_.getBlock(true);
    if(block == nullptr) return false;
    return MaterialHelper::isOccluded(block->getMaterial()) && (location_.getY()-location_.getBlockX())==0.0;
}

Vec2d Entity::getVelocity() const {
    return velocity_;
}

