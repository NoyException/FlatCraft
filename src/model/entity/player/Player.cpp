//
// Created by Noy on 2023/7/4.
//

#include "model/entity/player/Player.h"
#include "model/FlatCraft.h"
#include "model/event/instance/normal/EntityTeleportEvent.h"

Player::Player(const Location &spawnLocation) : LivingEntity(spawnLocation),
currentSlot_(0), cursor_(Material::AIR), lastBreaking_(nullptr), breakingProgress_(0),
walkingDirection_(0), sprinting_(false), sneaking_(false), flying_(false){

    EventManager::registerListener(EventType::ENTITY_TELEPORT_EVENT,EventPriority::MONITOR,[&](EventInstance* event){
        auto e = dynamic_cast<EntityTeleportEvent*>(event);
        if(!e->isCanceled() && e->getEntity()==this){
            auto target = e->getTargetLocation().getWorld();
            auto old = location_.getWorld();
            if(target!=old){
                if(old != nullptr) old->stop();
                if(target != nullptr) target->run();
            }
        }
    });
}

Player::~Player() {
    task_->cancel();
}

nlohmann::json Player::serialize() const {
    return std::move(LivingEntity::serialize());
}

std::unique_ptr<Player> Player::deserialize(const nlohmann::json &json) {
    auto player = std::make_unique<Player>(Location::deserialize(json.at("location")));
    player->health_ = json.at("health").get<double>();
    return std::move(player);
}

void Player::control() {
    //走路
    bool onGround = isOnGround();
    double dx = onGround ? 0.2 : 0.05;
    if(sprinting_) dx*=1.5;
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
        Location start = location_;
        start.add(velocity_.getX(),aabb.getHeight()/2);
        auto res = getWorld()->rayTrace(start,{0,-1},0.5,aabb.getWidth()/2,aabb.getHeight()/2,
                                        [](Material material){return true;},[](Entity* entity){return false;});
        if(res==nullptr)
            velocity_.setX(0);
    }
    if(stopSprinting) sprinting_ = false;
}

void Player::jump() {
    if(isOnGround()) velocity_.setY(0.2);
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
    bool resetBreakingProgress = true;
    auto world = getWorld();
    auto block = world->getBlock(position, true);
    if (MaterialHelper::isAir(block->getMaterial()) || MaterialHelper::isLiquid(block->getMaterial()))
        block = world->getBlock(position, false);
    if (block != nullptr) {
        if (block == lastBreaking_) {
            double hardness = MaterialHelper::getHardness(block->getMaterial());
            if (hardness > 0) breakingProgress_ += 0.05 / hardness;
            if (hardness == 0) breakingProgress_ = 1;
            if (hardness < 0) breakingProgress_ = 0;
            if (breakingProgress_ > 1.0) breakingProgress_ = 1.0;
            if (breakingProgress_ == 1.0) {
                block->setMaterial(Material::AIR);
            }
            resetBreakingProgress = false;

            setDirection(position - location_.toVec2d());
        } else lastBreaking_ = block;
    }
    if(resetBreakingProgress) breakingProgress_ = 0;
}

int Player::getCurrentSlot() const {
    return currentSlot_;
}

double Player::getBreakingProgress() const {
    return breakingProgress_;
}
