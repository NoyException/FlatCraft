//
// Created by Noy on 2023/7/4.
//

#include "model/entity/player/Player.h"
#include "model/FlatCraft.h"
#include "model/event/instance/normal/EntityTeleportEvent.h"

Player::Player(const Location &spawnLocation) : LivingEntity(spawnLocation),
currentSlot_(0), cursor_(Material::AIR), lastBreaking_(nullptr), breakingProgress_(0),
walkingDirection_(0), sprinting_(false), sneaking_(false), flying_(false){

    EventManager::registerListener<EntityTeleportEvent>(EventPriority::MONITOR,[&](EntityTeleportEvent* event){
        if(!event->isCanceled() && event->getEntity()==this){
            auto target = event->getTargetLocation().getWorld();
            auto old = location_.getWorld();
            if(target!=old){
                if(old != nullptr) old->stop();
                if(target != nullptr) target->run();
            }
        }
    });
}

Player::~Player() = default;

Player::Player(const nlohmann::json &json) : LivingEntity(json),
cursor_(json.at("cursor")), currentSlot_(0), lastBreaking_(nullptr), breakingProgress_(0),
walkingDirection_(0), sprinting_(false), sneaking_(false), flying_(false){

}

std::unique_ptr<Player> Player::deserialize(const nlohmann::json &json) {
    return std::make_unique<Player>(json);
}

std::unique_ptr<nlohmann::json> Player::serialize() const {
    auto json = LivingEntity::serialize();
    json->merge_patch(nlohmann::json{{"cursor",*cursor_.serialize()}});
    return json;
}

void Player::control() {
    //走路
    bool onGround = isOnGround();
    double dx = onGround ? 0.2 : 0.05;
    if(sprinting_) dx*=1.3;
    if(sneaking_) dx*=0.3;
    bool stopSprinting;
    if(walkingDirection_<0){
        if(onGround){
            velocity_.setX(std::max(-dx,velocity_.getX()-0.08));
        }
        else if(velocity_.getX()>-dx){
            velocity_.setX(std::max(-dx,velocity_.getX()-0.02));
        }
        friction_ = false;
        stopSprinting = false;
    }
    else if(walkingDirection_>0){
        if(onGround){
            velocity_.setX(std::min(dx,velocity_.getX()+0.08));
        }
        else if(velocity_.getX()<dx){
            velocity_.setX(std::min(dx,velocity_.getX()+0.02));
        }
        friction_ = false;
        stopSprinting = false;
    }
    else{
        friction_ = true;
        stopSprinting = true;
    }
    //下蹲边缘检测
    if(onGround && sneaking_ && std::abs(velocity_.getX())<0.1){

        auto aabb = getBoundingBox();
        Vec2d start = location_.toVec2d() + Vec2d(velocity_.getX(),aabb.getHeight()/2);
        auto res = getWorld()->rayTrace(start,{0,-1},0.5,aabb.getWidth()/2,aabb.getHeight()/2);
        if(res==nullptr)
            velocity_.setX(0);
    }
    if(stopSprinting) sprinting_ = false;
}

void Player::jump() {
    if(isOnGround()) velocity_.setY(0.25);
}

BoundingBox Player::getBoundingBox() const {
    BoundingBox aabb = Entity::getBoundingBox();
    aabb.expand(0.4,0,0.4,1.8);
    return aabb;
}

bool Player::isFlying() const {
    return flying_;
}

void Player::setFlying(bool flying) {
    gravity_ = !flying;
    flying_ = flying;
    if(flying) velocity_ = {};
}

int Player::getWalkingDirection() const {
    return walkingDirection_;
}

void Player::setWalkingDirection(int walkingDirection) {
    walkingDirection_ = walkingDirection;
}

bool Player::isSprinting() const {
    return sprinting_;
}

void Player::setSprinting(bool sprinting) {
    sprinting_ = sprinting;
}

bool Player::isSneaking() const {
    return sneaking_;
}

void Player::setSneaking(bool sneaking) {
    sprinting_ = false;
    sneaking_ = sneaking;
}

void Player::tryToBreak(const Vec2d &position) {
    auto world = getWorld();
    auto block = world->getBlock(position, true);
    Vec2d start = location_.toVec2d() + Vec2d(0,0.9);
    Vec2d direction = position - location_.toVec2d();
    //判断是否能挖到
    auto res = world->rayTrace(start, direction, 6, 0, 0, false,
                               [](Block* block){return MaterialHelper::isOccluded(block->getMaterial());},
                               [&](Entity* entity){return entity!=this;});
    if(res!=nullptr && res->getHitBlock()!=block && (res->getHitPoint()->toBlockLocation().toVec2d()-start).lengthSquared() <
                               (block->getLocation().toVec2d()-start).lengthSquared()) return;

    if (MaterialHelper::isAir(block->getMaterial()) || MaterialHelper::isLiquid(block->getMaterial()))
        block = world->getBlock(position, false);
    if (block != nullptr && !MaterialHelper::isAir(block->getMaterial())
    && !MaterialHelper::isLiquid(block->getMaterial())) {
        if (block == lastBreaking_) {
            double hardness = MaterialHelper::getHardness(block->getMaterial());
//            std::cout<<hardness<<" "<<breakingProgress_<<std::endl;
            if (hardness > 0) breakingProgress_ += 0.05 / hardness;
            if (hardness == 0) breakingProgress_ = 1;
            if (hardness < 0) breakingProgress_ = 0;
            if (breakingProgress_ > 1.0) breakingProgress_ = 1.0;
            if (breakingProgress_ >= 1.0) {
                block->setMaterial(Material::AIR);
                breakingProgress_ = 0;
            }
            setDirection(direction);
        }
        else {
            lastBreaking_ = block;
            breakingProgress_ = 0;
        }
    }
}

int Player::getCurrentSlot() const {
    return currentSlot_;
}

double Player::getBreakingProgress() const {
    return breakingProgress_;
}

void Player::stopBreaking() {
    breakingProgress_ = 0;
}
