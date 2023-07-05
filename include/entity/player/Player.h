//
// Created by Noy on 2023/7/4.
//

#ifndef FLATCRAFT_PLAYER_H
#define FLATCRAFT_PLAYER_H

#include "common.h"
#include "entity/LivingEntity.h"

class Player : public LivingEntity{
public:
    explicit Player(const Location& spawnLocation);
    [[nodiscard]] nlohmann::json serialize() const override;
    static Player deserialize(const nlohmann::json& json);
private:
};


#endif //FLATCRAFT_PLAYER_H
