//
// Created by Noy on 2023/7/4.
//

#include "entity/player/Player.h"

Player::Player(const Location &spawnLocation) : LivingEntity(spawnLocation) {

}

nlohmann::json Player::serialize() const {
    return LivingEntity::serialize();
}

Player Player::deserialize(const nlohmann::json &json) {
    Player &&player = Player{Location::deserialize(json.at("location"))};
    player.health_ = json.at("health").get<double>();
    return player;
}
