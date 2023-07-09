//
// Created by Noy on 2023/7/6.
//

#include "PlayerController.h"

PlayerController PlayerController::instance_;

PlayerController::PlayerController() : states_(), wheelY_(0) {
    reset();
}

void PlayerController::setKeyState(Key key, KeyState state) {
    states_[static_cast<int>(key)] = state;
}

KeyState PlayerController::getKeyState(Key key) const{
    return states_[static_cast<int>(key)];
}

double PlayerController::getWheelY() const {
    return wheelY_;
}

void PlayerController::setWheelY(double wheelY) {
    wheelY_ = wheelY;
}

const Vec2d &PlayerController::getClickPosition() const {
    return clickPosition_;
}

void PlayerController::setClickPosition(const Vec2d &clickPosition) {
    clickPosition_ = clickPosition;
}

void PlayerController::reset() {
    for (auto &item: states_){
        item = KeyState::UP;
    }
    wheelY_ = 0;
}

