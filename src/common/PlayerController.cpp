//
// Created by Noy on 2023/7/6.
//

#include "PlayerController.h"

PlayerController PlayerController::instance_;

PlayerController::PlayerController() : states_() {
    reset();
}

void PlayerController::setKeyState(Key key, KeyState state) {
    states_[static_cast<int>(key)] = state;
}

KeyState PlayerController::getKeyState(Key key) const{
    return states_[static_cast<int>(key)];
}

void PlayerController::reset() {
    for (auto &item: states_){
        item = KeyState::UP;
    }
}
