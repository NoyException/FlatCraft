//
// Created by Noy on 2023/7/10.
//

#include "PlayerViewModel.h"
#include "model/FlatCraft.h"

PlayerViewModel::PlayerViewModel(Player *player) : EntityViewModel(player), states_(), scrollY_(0),
cursor_(player->cursor_==nullptr?MaterialStack():player->cursor_->toMaterialStack()), inventory_(){
    for (auto &item: states_){
        item = KeyState::UP;
    }
    for (int i = 0; i < player->getInventory()->getCapacity(); ++i){
        auto itemStack = player->getInventory()->get(i);
        if(itemStack!= nullptr) inventory_[i] = itemStack->toMaterialStack();
        else inventory_[i] = MaterialStack();
    }
}

Player *PlayerViewModel::getPlayer() {
    return dynamic_cast<Player*>(entity_);
}

std::function<void(Key, KeyState)> PlayerViewModel::getCommandChangeKeyState() {
    return [&](Key key, KeyState state){
        states_[static_cast<int>(key)] = state;
    };
}

std::function<void(double)> PlayerViewModel::getCommandScrollMouseWheel() {
    return [&](double scrollY){
        scrollY_ = scrollY;
    };
}

std::function<void(const Vec2d &)> PlayerViewModel::getCommandChangeCursorPosition() {
    return [&](const Vec2d &v){
        cursorPosition_ = v;
    };
}

std::function<void(int)> PlayerViewModel::getCommandClickedSlot() {
    return [&](int slot){
        getPlayer()->clickSlot(slot);
    };
}

std::function<void(RefPtr<int>)> PlayerViewModel::getBinderCurrentSlot() {
    return [&](RefPtr<int> ptr) {
        ptr.pointTo(getPlayer()->currentSlot_);
    };
}

std::function<void(RefPtr<bool>)> PlayerViewModel::getBinderSneaking() {
    return [&](RefPtr<bool> ptr) {
        ptr.pointTo(getPlayer()->sneaking_);
    };
}

std::function<void(RefPtr<Vec2d>, RefPtr<double>)> PlayerViewModel::getBinderBreakingBlock() {
    return [&](RefPtr<Vec2d> position, RefPtr<double> progress) {
        position.pointTo(breakingPosition_);
        progress.pointTo(getPlayer()->breakingProgress_);
    };
}

std::function<void(RefPtr<MaterialStack>)> PlayerViewModel::getBinderCursor() {
    return [&](RefPtr<MaterialStack> ptr) {
        ptr.pointTo(cursor_);
    };
}

std::function<void(RefPtr<MaterialStack>)> PlayerViewModel::getBinderInventory() {
    return [&](RefPtr<MaterialStack> ptr) {
        ptr.pointTo(inventory_[0]);
    };
}

void PlayerViewModel::setNotificationCurrentSlotChanged(const std::function<void()> &notificationCurrentSlotChanged) {
    notificationCurrentSlotChanged_ = notificationCurrentSlotChanged;
}

bool PlayerViewModel::isPressed(Key key) {
    return states_[static_cast<int>(key)]==KeyState::DOWN;
}

void PlayerViewModel::control() {
    auto player = getPlayer();
    //键盘行为：
    //飞行模式
    if(isPressed(Key::SPACE)){
        player->setFlying(true);
        auto loc = player->getLocation();
        if(isPressed(Key::UP)) loc.add(0,0.2);
        if(isPressed(Key::DOWN)) loc.add(0,-0.2);
        if(isPressed(Key::LEFT)) loc.add(-0.2,0);
        if(isPressed(Key::RIGHT)) loc.add(0.2,0);
        player->teleport(loc);
    }
    else{
        player->setFlying(false);
    }
    //左右移动
    bool pressLeft = isPressed(Key::LEFT);
    bool pressRight = isPressed(Key::RIGHT);
    if(pressLeft && !pressRight)
        player->setWalkingDirection(-1);
    else if(!pressLeft && pressRight)
        player->setWalkingDirection(1);
    else
        player->setWalkingDirection(0);
    //下蹲、奔跑与跳跃
    if(isPressed(Key::SHIFT)){
        if(!player->isSneaking()){
            player->setSneaking(true);
            notificationSneakingStateChanged_();
        }
    }
    else{
        if(player->isSneaking()){
            player->setSneaking(false);
            notificationSneakingStateChanged_();
        }
    }
    if(isPressed(Key::CTRL)){
        if(!player->isSprinting()){
            player->setSprinting(true);
        }
    }
    if(isPressed(Key::UP))
        player->jump();
    //挖掘
    double progress = player->getBreakingProgress();
    if(isPressed(Key::LEFT_CLICK)){
        player->tryToBreak(cursorPosition_);
    }
    else player->stopBreaking();
    if(progress!=player->getBreakingProgress()){
        if(player->lastBreaking_==nullptr) breakingPosition_ = {0,0};
        else breakingPosition_ = player->lastBreaking_->getLocation().toVec2d();
        notificationBreakingBlockChanged_();
    }
    //放置
    if(isPressed(Key::RIGHT_CLICK)){
        if(!isRightClickPressedLastTick_){
            player->tryToPlace(cursorPosition_);
            isRightClickPressedLastTick_ = true;
        }
    }
    else isRightClickPressedLastTick_ = false;
    //滚轮滚动
    int oldSlot = player->getCurrentSlot();
    int slot = (int)std::round(-scrollY_)+oldSlot;
    if(slot<0) slot+=(1-slot/9)*9;
    slot%=9;
    if(slot!=oldSlot){
        player->setCurrentSlot(slot);
    }
    scrollY_ = 0;
    //玩家行动
    player->control();
}

void PlayerViewModel::setNotificationSneakingStateChanged(const std::function<void()> &notificationSneakingStateChanged) {
    notificationSneakingStateChanged_ = notificationSneakingStateChanged;
}

void PlayerViewModel::setNotificationBreakingBlockChanged(
        const std::function<void()> &notificationBreakingBlockChanged) {
    notificationBreakingBlockChanged_ = notificationBreakingBlockChanged;
}

void PlayerViewModel::setNotificationCursorChanged(const std::function<void()> &notificationCursorChanged) {
    notificationCursorChanged_ = notificationCursorChanged;
}

void PlayerViewModel::setNotificationInventoryChanged(const std::function<void(int)> &notificationInventoryChanged) {
    notificationInventoryChanged_ = notificationInventoryChanged;
}

void PlayerViewModel::onBound() {
    EntityViewModel::onBound();

    listener1_ = EventManager::registerListener<ValueChangedNotification<Player>>(EventPriority::MONITOR, [&](auto *event) {
        auto player = getPlayer();
        if(event!=nullptr && event->getObject()==player){
            switch(event->getField()){
                case Field::PLAYER_CURSOR:{
                    cursor_ = player->cursor_==nullptr?MaterialStack():player->cursor_->toMaterialStack();
                    notificationCursorChanged_();
                    break;
                }
                case Field::PLAYER_CURRENT_SLOT:{
                    notificationCurrentSlotChanged_();
                }
                default:
                    break;
            }
        }
    });

    listener2_ = EventManager::registerListener<ValueChangedNotification<PlayerInventory>>(EventPriority::MONITOR, [&](ValueChangedNotification<PlayerInventory> *event) {
        auto player = getPlayer();
        if(event!=nullptr && event->getObject()==player->getInventory()){
            switch(event->getField()){
                case Field::PLAYER_INVENTORY:{
                    int index = event->template getPayload<int>();
                    auto itemStack = player->getInventory()->get(index);
                    if(itemStack != nullptr) inventory_[index] = itemStack->toMaterialStack();
                    else inventory_[index] = MaterialStack();
                    notificationInventoryChanged_(index);
                    break;
                }
                default:
                    break;
            }
        }
    });

    FlatCraft::getInstance()->getScheduler()->runTaskTimer([&](){
        control();
    },1,0);
}

PlayerViewModel::~PlayerViewModel() {
    if(listener1_!=nullptr)
        EventManager::unregisterListener(listener1_);
    if(listener2_!=nullptr)
        EventManager::unregisterListener(listener2_);
}
