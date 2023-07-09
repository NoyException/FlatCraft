//
// Created by Noy on 2023/7/3.
//

#include "entity/Entity.h"
#include "world/World.h"
#include "FlatCraft.h"
#include "event/instance/EntityTeleportEvent.h"

Entity::Entity(const Location &spawnLocation) : location_(spawnLocation), velocity_(), friction_(true), gravity_(true){
    physicsTask_ = FlatCraft::getInstance()->getScheduler()->runTaskTimer([&]() {
        if(isOnGround()){
            if(friction_){
                double x = velocity_.getX();
                if(x<0) {
                    velocity_.setX(std::min(0.0,x+0.1));
                }
                else if(x>0){
                    velocity_.setX(std::max(0.0,x-0.1));
                }
            }
        }
        else {
            if(gravity_){
                velocity_.add(0, -0.02);
            }
        }
        velocity_.adjust();
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

void Entity::move(const Vec2d &v) {
    Vec2d dv = v;
    dv.adjust();
    Location start = location_;
    auto aabb = getBoundingBox();
    start.add(0,aabb.getHeight()/2);
    auto res = getWorld()->rayTrace(start,dv,dv.length(),aabb.getWidth()/2,aabb.getHeight()/2,
                                   [](Material material){return true;},[](Entity* entity){return false;});
    if(res==nullptr){
       location_.add(dv);
    }
    else{
       auto dv2 = res->getHitPoint()->toVec2d()-start.toVec2d();
       if(dv2.lengthSquared()<dv.lengthSquared()){
           location_.add(dv2);
           switch (res->getHitFace()) {
               case BoundingBox::Face::LEFT:
               case BoundingBox::Face::RIGHT:
                   velocity_.setX(0);
                   break;
               case BoundingBox::Face::TOP:
               case BoundingBox::Face::BOTTOM:
                   velocity_.setY(0);
                   break;
           }
       }
       else location_.add(dv);
    }
    location_.adjust();
}

nlohmann::json Entity::serialize() const {
    return {{"location",location_.serialize()}};
}

bool Entity::isOnGround() const {
    if(abs(location_.getY()-std::round(location_.getY()))>0.000001) return false;

    Location start = location_;
    auto aabb = getBoundingBox();
    start.add(0,aabb.getHeight()/2);
    auto res = getWorld()->rayTrace(start,Vec2d(0,-1),0.000001,aabb.getWidth()/2,aabb.getHeight()/2,
                                    [](Material material){return true;},[](Entity* entity){return false;});
    return res!= nullptr;
//    auto aabb = getBoundingBox();
//    auto world = getWorld();
//
//    int y = location_.getBlockY();
//    for(int i = std::ceil(location_.getX()-aabb.getWidth()/2), endI = std::ceil(location_.getX()+aabb.getWidth()/2);
//    i <= endI; i++){
//        auto block = world->getBlock(i,y, true);
//        if(block != nullptr && MaterialHelper::isOccluded(block->getMaterial())) return true;
//    }
//    return false;
}

Vec2d Entity::getVelocity() const {
    return velocity_;
}

void Entity::setVelocity(const Vec2d &velocity) {
    velocity_ = velocity;
}

BoundingBox Entity::getBoundingBox() const {
    return {location_.getX(),location_.getY(),location_.getX(),location_.getY()};
}

bool Entity::hasFriction() const {
    return friction_;
}

bool Entity::hasGravity() const {
    return gravity_;
}

