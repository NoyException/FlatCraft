//
// Created by Noy on 2023/7/4.
//

#include "entity/player/Player.h"
#include "entity/player/PlayerController.h"
#include "FlatCraft.h"

Player::Player(const Location &spawnLocation) : LivingEntity(spawnLocation), controller_() {
    task_ = FlatCraft::getInstance()->getScheduler()->runTaskTimer([&](){
        controller_.locked_ = true;
        bool onGround = isOnGround();
        if(controller_.ctrl_){
            sprinting_ = true;
        }
        if(controller_.shift_){
            sprinting_ = false;
            sneaking_ = true;
        }
        else sneaking_ = false;
        if(controller_.up_){
            if(onGround) jump();
        }
        double dx = onGround ? 0.2 : 0.05;
        if(sprinting_) dx*=1.3;
        if(sneaking_) dx*=0.3;
        if(controller_.left_){
            location_.add(-dx,0);
        }
        if(controller_.right_){
            location_.add(dx,0);
        }
        controller_.reset();
    },0,0);
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

PlayerController *Player::getController() {
    return &controller_;
}

void Player::jump() {
    velocity_.setY(0.2);
}
