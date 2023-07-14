//
// Created by Noy on 2023/7/3.
//

#include "model/entity/Entity.h"
#include "model/world/World.h"
#include "model/FlatCraft.h"
#include "model/event/events.h"

Entity::Entity() :
location_(Location::INVALID_LOCATION), direction_(), velocity_(),
friction_(true), gravity_(true), id_(-1){}

Entity::~Entity() {
    if(physicsTask_ != nullptr){
        physicsTask_->cancel();
        physicsTask_ = nullptr;
    }
}

Entity::Entity(const nlohmann::json &json) : id_(-1),
location_(json.at("location")), velocity_(json.at("velocity")),
gravity_(json.at("gravity").get<bool>()), friction_(json.at("friction").get<bool>()){
    FlatCraft::getInstance()->getScheduler()->runTask([&](){
        notifyJoinWorld(getWorld());
    });
}

std::unique_ptr<nlohmann::json> Entity::serialize() const {
    return std::make_unique<nlohmann::json>(nlohmann::json::initializer_list_t{
        {"type",static_cast<int>(getType())},
        {"location",location_.serialize()},
        {"direction",direction_.serialize()},
        {"velocity",velocity_.serialize()},
        {"gravity",gravity_},
        {"friction",friction_}});
}

std::unique_ptr<Entity> Entity::deserialize(const nlohmann::json& json) {
    switch (static_cast<EntityType>(json.at("type").get<int>())) {
        case EntityType::PLAYER:
            return std::make_unique<Player>(json);
        case EntityType::DROPPED_ITEM:
            return std::make_unique<DroppedItem>(json);
        default:
            return nullptr;
    }
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
    World* oldWorld = location_.getWorld();
    World* newWorld = targetLocation.getWorld();
    location_ = targetLocation;
    if(newWorld!=oldWorld){
        if(oldWorld != nullptr){
            notifyLeaveWorld(oldWorld);
            oldWorld->notifyEntityLeave(this);
        }
        if(newWorld != nullptr){
            notifyJoinWorld(newWorld);
            newWorld->notifyEntityJoin(this);
        }
    }
    ValueChangedNotification notification(this,Field::ENTITY_POSITION,location_.toVec2d());
    EventManager::callEvent(notification);
}

Vec2d Entity::getDirection() const {
    return direction_;
}

void Entity::setDirection(const Vec2d &direction) {
    direction_ = direction;
    ValueChangedNotification notification(this,Field::ENTITY_DIRECTION,direction_);
    EventManager::callEvent(notification);
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
    if(location_.getY()<-32 && v.getY()<0) return;
    Vec2d dv = v;
    dv.adjust();
    auto aabb = getBoundingBox();
    Vec2d start = location_.toVec2d()+Vec2d(0,aabb.getHeight()/2);
    auto res = getWorld()->rayTrace(start,dv,dv.length(),aabb.getWidth()/2,aabb.getHeight()/2);
    if(res==nullptr){
       location_.add(dv);
    }
    else{
        auto dv2 = res->getHitPoint()->toVec2d()-start;
        if(dv2.lengthSquared()<dv.lengthSquared()){
            switch (res->getHitFace()) {
                case BoundingBox::Face::LEFT:
                case BoundingBox::Face::RIGHT:
//                    std::cout<<"#paused";
                    velocity_.setX(0);
                    break;
                case BoundingBox::Face::TOP:
                case BoundingBox::Face::BOTTOM:
                    velocity_.setY(0);
                    break;
            }
            location_.add(dv2);
        }
        else location_.add(dv);
    }
    location_.adjust();
    ValueChangedNotification notification(this,Field::ENTITY_POSITION,location_.toVec2d());
    EventManager::callEvent(notification);
    ValueChangedNotification notification2(this,Field::ENTITY_VELOCITY,velocity_);
    EventManager::callEvent(notification2);
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
    if(std::abs(d-std::round(d))>0.000001) return false;
    Vec2d start = location_.toVec2d() + Vec2d(0,aabb.getHeight()/2);
    auto res = getWorld()->rayTrace(start,dir,0.000001,
                                    aabb.getWidth()/2,aabb.getHeight()/2,false,[](const Block* block){
        return MaterialHelper::isOccluded(block->getMaterial());
    });
    return res!= nullptr;
}

bool Entity::isOnGround() const {
    return isCollided(BoundingBox::Face::BOTTOM);
}

bool Entity::isStandingOn(Material blockMaterial) const {
    if(!isOnGround()) return false;
    auto aabb = getBoundingBox();
    aabb.expand(0.499999,0.499999,0.499999,0.499999);
    aabb.shift(-0.5,-0.5);
    auto world = getWorld();
    int y = location_.getBlockY()-1;
    for(int x = std::ceil(aabb.getMinX()),endX = std::ceil(aabb.getMaxX());x<endX;x++){
        if(world->getBlock(x,y,true)->getMaterial()==blockMaterial)
            return true;
    }
    return false;
}

bool Entity::isTouching(Material blockMaterial) const {
    auto aabb = getBoundingBox();
    aabb.expand(0.499999,0.499999,0.499999,0.499999);
    aabb.shift(-0.5,-0.5);
    auto world = getWorld();
    for(int x = std::ceil(aabb.getMinX()),endX = std::ceil(aabb.getMaxX());x<endX;x++){
        for(int y = std::ceil(aabb.getMinY()),endY = std::ceil(aabb.getMaxY());y<endY;y++){
            if(world->getBlock(x,y,true)->getMaterial()==blockMaterial)
                return true;
        }
    }
    return false;
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

void Entity::run() {}

void Entity::remove() {
    notifyLeaveWorld(getWorld());
    FlatCraft::getInstance()->destroyEntity(this);
}

int Entity::getId() const {
    return id_;
}

void Entity::notifyJoinWorld(World *world) {
    if(physicsTask_!=nullptr){
        physicsTask_->cancel();
    }
    startPhysicalTask();
}

void Entity::notifyLeaveWorld(World *world) {
    if(physicsTask_!= nullptr) {
        physicsTask_->cancel();
        physicsTask_ = nullptr;
    }
}

bool Entity::isSpawned() const {
    return !location_.getRawWorld().empty();
}

void Entity::startPhysicalTask() {
    physicsTask_ = FlatCraft::getInstance()->getScheduler()->runTaskTimer([&]() {
        bool onGround = isOnGround();
        bool touchingWater = isTouching(Material::WATER);

        double vx = velocity_.getX();
        double vy = velocity_.getY();
        if(touchingWater){
            if(vx<0) {
                velocity_.setX(std::min(0.0,vx+0.01));
            }
            else if(vx>0){
                velocity_.setX(std::max(0.0,vx-0.01));
            }
        }
        else if(onGround && friction_){
            if(vx<0) {
                velocity_.setX(std::min(0.0,vx+0.1));
            }
            else if(vx>0){
                velocity_.setX(std::max(0.0,vx-0.1));
            }
        }

        if(!onGround) {
            if(gravity_){
                if(touchingWater){
                    velocity_.setY(std::max(-0.1, vy - 0.005));
                }
                else{
                    velocity_.setY(std::max(-1.0, vy - 0.025));
                }
            }
        }
        velocity_.adjust();
        vx = velocity_.getX();
        vy = velocity_.getY();
        if(vx != 0)
            setDirection({vx, direction_.getY()});
        if(vy != 0)
            setDirection({direction_.getX(), vy});

        if(vx > 0 && isCollided(BoundingBox::Face::RIGHT)){
            velocity_.setX(0);
        }
        if(vx < 0 && isCollided(BoundingBox::Face::LEFT)) velocity_.setX(0);
        if(vy > 0 && isCollided(BoundingBox::Face::TOP)) velocity_.setY(0);
        if(vy < 0 && onGround) velocity_.setY(0);
        move();
        run();
    },0,0);
}

