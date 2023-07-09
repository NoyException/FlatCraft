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

void PlayerController::reset() {
    for (auto &item: states_){
        item = KeyState::UP;
    }
    wheelY_ = 0;
}

const std::optional<Vec2d> &PlayerController::getLeftClickPosition() const {
    return leftClickPosition_;
}

void PlayerController::setLeftClickPosition(const std::optional<Vec2d> &leftClickPosition) {
    PlayerController::leftClickPosition_ = leftClickPosition;
}

const std::optional<Vec2d> &PlayerController::getRightClickPosition() const {
    return rightClickPosition_;
}

void PlayerController::setRightClickPosition(const std::optional<Vec2d> &rightClickPosition) {
    PlayerController::rightClickPosition_ = rightClickPosition;
}
