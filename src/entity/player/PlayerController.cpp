//
// Created by Noy on 2023/7/6.
//

#include "entity/player/PlayerController.h"

void PlayerController::up() {
    if(locked_) return;
    up_ = true;
}

void PlayerController::down() {
    if(locked_) return;
    down_ = true;
}

void PlayerController::left() {
    if(locked_) return;
    left_ = true;
}

void PlayerController::right() {
    if(locked_) return;
    right_ = true;
}

void PlayerController::space() {
    if(locked_) return;
    space_ = true;
}

void PlayerController::shift() {
    if(locked_) return;
    shift_ = true;
}

void PlayerController::ctrl() {
    if(locked_) return;
    ctrl_ = true;
}

void PlayerController::leftClick() {
    if(locked_) return;
    leftClick_ = true;
}

void PlayerController::rightClick() {
    if(locked_) return;
    rightClick_ = true;
}

void PlayerController::reset() {
    up_ = false;
    down_ = false;
    left_ = false;
    right_ = false;
    space_ = false;
    shift_ = false;
    ctrl_ = false;
    leftClick_ = false;
    rightClick_ = false;
    locked_ = false;
}
