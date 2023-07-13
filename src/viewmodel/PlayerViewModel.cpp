//
// Created by Noy on 2023/7/10.
//

#include "PlayerViewModel.h"
#include "model/FlatCraft.h"

PlayerViewModel::PlayerViewModel(Player *player) : EntityViewModel(player), states_(), scrollY_(0) {
    for (auto &item: states_){
        item = KeyState::UP;
    }
    FlatCraft::getInstance()->getScheduler()->runTaskTimer([&](){
        //暂停
        do{
            if(isPressed(Key::ESC)){
                if(!isEscPressedLastTick_){
                    isPaused_ = !isPaused_;
                }
                isEscPressedLastTick_ = true;
            }
            else isEscPressedLastTick_ = false;
            if(isPaused_) std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }while(isPaused_ && FlatCraft::getInstance()->getScheduler()->isRunning());
        control();
    },1,0);
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
        notificationCurrentSlotChanged_();
    };
}

std::function<void(const Vec2d &)> PlayerViewModel::getCommandChangeCursorPosition() {
    return [&](const Vec2d &v){
        cursorPosition_ = v;
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

std::function<void(RefPtr<double>)> PlayerViewModel::getBinderBreakingProgress() {
    return [&](RefPtr<double> ptr) {
        ptr.pointTo(getPlayer()->breakingProgress_);
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
    player->setSprinting(isPressed(Key::CTRL));
    if(isPressed(Key::UP))
        player->jump();
    //挖掘与放置
    double progress = player->getBreakingProgress();
    if(isPressed(Key::LEFT_CLICK)){
        player->tryToBreak(cursorPosition_);
    }
    else player->stopBreaking();
    if(progress!=player->getBreakingProgress())
        notificationBreakingProgressChanged_();
    //TODO: 滚轮滚动
    //
    player->control();
}

void PlayerViewModel::setNotificationSneakingStateChanged(const std::function<void()> &notificationSneakingStateChanged) {
    notificationSneakingStateChanged_ = notificationSneakingStateChanged;
}

void PlayerViewModel::setNotificationBreakingProgressChanged(
        const std::function<void()> &notificationBreakingProgressChanged) {
    notificationBreakingProgressChanged_ = notificationBreakingProgressChanged;
}
