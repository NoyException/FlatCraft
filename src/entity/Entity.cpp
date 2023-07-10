//
// Created by Noy on 2023/7/3.
//

#include "entity/Entity.h"
#include "world/World.h"
#include "FlatCraft.h"
#include "event/instance/EntityTeleportEvent.h"

Entity::Entity(const Location &spawnLocation, const Vec2d& direction) : location_(spawnLocation), direction_(direction), velocity_(),
friction_(true), gravity_(true){
    physicsTask_ = FlatCraft::getInstance()->getScheduler()->runTaskTimer([&]() {
        bool onGround = isOnGround();
        if(onGround){
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
//        if(velocity_.getX()>0){
//            std::cout<<"*";
//        }
        if(velocity_.getX()!=0) direction_.setX(velocity_.getX());
        if(velocity_.getY()!=0) direction_.setY(velocity_.getY());

        if(velocity_.getX()>0 && isCollided(BoundingBox::Face::RIGHT)) velocity_.setX(0);
        if(velocity_.getX()<0 && isCollided(BoundingBox::Face::LEFT)) velocity_.setX(0);
        if(velocity_.getY()>0 && isCollided(BoundingBox::Face::TOP)) velocity_.setY(0);
        if(velocity_.getY()<0 && onGround) velocity_.setY(0);
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

Vec2d Entity::getDirection() const {
    return direction_;
}

void Entity::setDirection(const Vec2d &direction) {
    direction_ = direction;
}

Vec2d Entity::getVelocity() const {
    return velocity_;
}

void Entity::setVelocity(const Vec2d &velocity) {
    velocity_ = velocity;
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

bool Entity::isCollided(BoundingBox::Face face) const {
    auto aabb = getBoundingBox();
    double d;
    Vec2d dir;
    switch (face) {
        case BoundingBox::Face::TOP:
            d = location_.getY()+aabb.getHeight();
            dir = {0,1};
            break;
        case BoundingBox::Face::BOTTOM:
            d = location_.getY();
            dir = {0,-1};
            break;
        case BoundingBox::Face::LEFT:
            d = location_.getX()-aabb.getWidth()/2;
            dir = {-1,0};
            break;
        case BoundingBox::Face::RIGHT:
            d = location_.getX()+aabb.getWidth()/2;
            dir = {1,0};
            break;
    }
    if(abs(d-std::round(d))>0.000001) return false;
    Location start = location_;
    start.add(0,aabb.getHeight()/2);
    auto res = getWorld()->rayTrace(start,dir,0.000001,aabb.getWidth()/2,aabb.getHeight()/2,
                                    [](Material material){return true;},[](Entity* entity){return false;});
    return res!= nullptr;
}

bool Entity::isOnGround() const {
    return isCollided(BoundingBox::Face::BOTTOM);
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

BoundingBox Entity::getBoundingBox() const {
    return {location_.getX(),location_.getY(),location_.getX(),location_.getY()};
}

bool Entity::hasFriction() const {
    return friction_;
}

bool Entity::hasGravity() const {
    return gravity_;
}
