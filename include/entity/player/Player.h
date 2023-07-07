//
// Created by Noy on 2023/7/4.
//

#ifndef FLATCRAFT_PLAYER_H
#define FLATCRAFT_PLAYER_H

#include "common.h"
#include "entity/LivingEntity.h"
#include "entity/player/PlayerController.h"

class Player : public LivingEntity{
public:
    explicit Player(const Location& spawnLocation);
    Player(const Player& another) = delete;
    ~Player() override;
    [[nodiscard]] nlohmann::json serialize() const override;
    static std::unique_ptr<Player> deserialize(const nlohmann::json& json);
    [[nodiscard]] PlayerController* getController();
private:
    void jump();
    PlayerController controller_;
    Task* task_;
    bool sprinting_;
    bool sneaking_;
};


#endif //FLATCRAFT_PLAYER_H
