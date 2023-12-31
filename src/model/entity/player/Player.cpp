//
// Created by Noy on 2023/7/4.
//

#include "model/entity/player/Player.h"
#include "model/FlatCraft.h"
#include "model/event/instance/normal/EntityTeleportEvent.h"

Player::Player() : LivingEntity(),
currentSlot_(0), cursor_(nullptr), lastBreaking_(nullptr), breakingProgress_(0),
walkingDirection_(0), sprinting_(false), sneaking_(false), flying_(false), inventory_(std::make_unique<PlayerInventory>()){

//    EventManager::registerListener<EntityTeleportEvent>(EventPriority::MONITOR,[&](EntityTeleportEvent* event){
//        if(!event->isCanceled() && event->getEntity()==this){
//            auto target = event->getTargetLocation().getWorld();
//            auto old = location_.getWorld();
//            if(target!=old){
//                if(old != nullptr) old->stop();
//                if(target != nullptr) target->run();
//            }
//        }
//    });

}

Player::Player(const nlohmann::json &json) : LivingEntity(json),
cursor_(nullptr), currentSlot_(0), lastBreaking_(nullptr), breakingProgress_(0),
walkingDirection_(0), sprinting_(false), sneaking_(false), flying_(false),
inventory_(dynamic_unique_cast<PlayerInventory>(Inventory::deserialize(json.at("inventory")))){
    if(json.contains("cursor")){
        cursor_ = ItemStack::deserialize(json.at("cursor"));
    }
}

std::unique_ptr<nlohmann::json> Player::serialize() const {
    auto json = LivingEntity::serialize();
    json->emplace("inventory",*inventory_->serialize());
    if(cursor_!=nullptr)
        json->emplace("cursor",*cursor_->serialize());
    return json;
}

void Player::control() {
    //走路
    bool onGround = isOnGround();
    bool touchingWater = isTouching(Material::WATER);
    double dx = 0.2;
    if(touchingWater) dx = 0.1;
    else if(!onGround) dx = 0.05;
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
    if(isTouching(Material::WATER)){
        auto aabb = getBoundingBox();
        aabb.expand(0.499999,0.499999,0.499999,0.499999);
        aabb.shift(-0.5,-0.5);
        auto world = getWorld();
        int y = std::floor(location_.getY()+0.2);
        bool emerge = true;
        bool sink = velocity_.getY()<0;
        for(int x = std::ceil(aabb.getMinX()),endX = std::ceil(aabb.getMaxX());x<endX;x++){
            if(world->getBlock(x,y,true)->getMaterial()==Material::WATER){
                emerge = false;
                break;
            }
        }
        if(emerge&&sink) return;
        velocity_.setY(std::min(emerge?0.2:0.1,velocity_.getY()+0.025));
    }
    else{
        if(isOnGround())
            velocity_.setY(0.25);
    }
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

bool Player::canTouch(const Vec2d &position) const {
    //世界边界检查
    Vec2d blockPos = position.toBlockPosition();
    if(blockPos.getY()<0 || blockPos.getY()>=256 || blockPos.getX()<-128 || blockPos.getX()>128)
        return false;
    //射线检查
    auto world = getWorld();
    auto block = world->getBlock(position, true);
    Vec2d start = location_.toVec2d() + Vec2d(0,0.9);
    static Vec2d D_POS[4] = {{0,0},{0,1},{1,0},{1,1}};
    for (const auto & v : D_POS) {
        Vec2d target = blockPos+v;
        Vec2d direction = target - start;
        //判断是否能挖到
        auto res = world->rayTrace(start, direction, 6, 0, 0, false,
                                   [](const Block* block){return MaterialHelper::isOccluded(block->getMaterial());},
                                   [&](const Entity* entity){return entity!=this;});
        if(res!=nullptr && res->getHitBlock()!=block &&
        (res->getHitPoint()->toBlockLocation().toVec2d()-start).lengthSquared() <
        (block->getLocation().toVec2d()-start).lengthSquared())
            continue;
        return true;
    }
    return false;
}

void Player::tryToBreak(const Vec2d &position) {
    if(!canTouch(position)) return;

    auto world = getWorld();
    auto block = world->getBlock(position, true);
    Vec2d start = location_.toVec2d() + Vec2d(0,0.9);
    Vec2d direction = position - start;

    if (!block->isBreakable())
        block = world->getBlock(position, false);
    if (block->isBreakable()) {
        if (block == lastBreaking_) {
            double hardness = MaterialHelper::getHardness(block->getMaterial());
            if (hardness > 0) breakingProgress_ += 0.05 / hardness;
            if (hardness == 0) breakingProgress_ = 1;
            if (hardness < 0) breakingProgress_ = 0;
            if (breakingProgress_ > 1.0) breakingProgress_ = 1.0;
            if (breakingProgress_ >= 1.0) {
                block->breakBy(this);
                breakingProgress_ = 0;
            }
            setDirection(direction);
        }
        else {
            lastBreaking_ = block;
            breakingProgress_ = 0;
        }
    }
    else{
        lastBreaking_ = nullptr;
        breakingProgress_ = 0;
    }
}

void Player::tryToPlace(const Vec2d &position) {
    if(!canTouch(position)) return;

    auto hand = getHand();
    if(ItemStackHelper::isAir(hand)) return;

    auto world = getWorld();
    static const Vec2d D_POS[4] = {{0,1},{1,0},{0,-1},{-1,0}};

    bool flag = true;
    for(int i=0;i<4 && flag;i++){
        for(int j=0;j<=1 && flag;j++){
            if(!world->getBlock(position+D_POS[i],j)->isAir())
                flag = false;
        }
    }
    if(flag) return;

    auto block = world->getBlock(position, true);
    if(!block->isReplaceable())
        return;
    auto behind = world->getBlock(position, false);

    if(behind->isReplaceable()){
        behind->setMaterial(hand->getMaterial());
    }
    else block->setMaterial(hand->getMaterial());

    auto stack = hand->clone();
    stack->setAmount(stack->getAmount()-1);
    setHand(std::move(stack));
}

int Player::getCurrentSlot() const {
    return currentSlot_;
}

void Player::setCurrentSlot(int currentSlot) {
    currentSlot_ = currentSlot;
    ValueChangedNotification notification(this,Field::PLAYER_CURRENT_SLOT,nullptr);
    EventManager::callEvent(notification);
}

double Player::getBreakingProgress() const {
    return breakingProgress_;
}

void Player::stopBreaking() {
    breakingProgress_ = 0;
}

void Player::notifyJoinWorld(World *world) {
    Entity::notifyJoinWorld(world);
    world->run();
}

void Player::notifyLeaveWorld(World *world) {
    Entity::notifyLeaveWorld(world);
    world->stop();
}

EntityType Player::getType() const {
    return EntityType::PLAYER;
}

PlayerInventory *Player::getInventory() {
    return inventory_.get();
}

const ItemStack* Player::getCursor() const {
    return cursor_.get();
}

void Player::setCursor(std::unique_ptr<ItemStack> &&cursor) {
    cursor_ = std::move(cursor);
    ValueChangedNotification notification(this,Field::PLAYER_CURSOR,cursor_.get());
    EventManager::callEvent(notification);
}

const ItemStack *Player::getHand() const {
    return inventory_->get(currentSlot_+36);
}

void Player::setHand(std::unique_ptr<ItemStack> &&hand) {
    inventory_->set(currentSlot_+36, std::move(hand));
}

void Player::clickSlot(int slotIndex) {
    if(slotIndex!=0){
        auto slot = inventory_->remove(slotIndex);
        inventory_->set(slotIndex,std::move(cursor_));
        setCursor(std::move(slot));
        if(slotIndex<=4){
            //摆烂了，先不调用Recipe模块了，后续维护需要改进（如果有的话）
            int logCnt = 0;
            int airCnt = 0;
            for (int i = 1; i <= 4; ++i) {
                if(ItemStackHelper::is(inventory_->get(i),Material::LOG))
                    logCnt++;
                else if(ItemStackHelper::isAir(inventory_->get(i)))
                    airCnt++;
            }
            if(logCnt==1 && airCnt==3){
                inventory_->set(0,std::make_unique<ItemStack>(Material::PLANKS,4));
            }
            else{
                inventory_->remove(0);
            }
        }
    }
    else{
        if(!ItemStackHelper::isAir(inventory_->get(0)) && ItemStackHelper::isAir(cursor_)){
            auto slot = inventory_->remove(0);
            setCursor(std::move(slot));
            for (int i = 1; i <= 4; ++i) {
                auto item = inventory_->remove(i);
                if(!ItemStackHelper::isAir(item)) item->setAmount(item->getAmount()-1);
                inventory_->set(i,std::move(item));
            }
        }
    }
}

void Player::respawn() {
    setHealth(20);
    auto world = getWorld();
    for(int i=255;i>=0;i--){
        if(MaterialHelper::isOccluded(world->getBlock(-1,i,true)->getMaterial()) ||
           MaterialHelper::isOccluded(world->getBlock(0,i,true)->getMaterial())){
            teleport(Location(*world,0,i+1));
            return;
        }
    }
}

void Player::onDie() {
    LivingEntity::onDie();
    respawn();
}

