//
// Created by Noy on 2023/7/4.
//

#ifndef FLATCRAFT_PLAYER_H
#define FLATCRAFT_PLAYER_H

#include "common.h"
#include "model/entity/LivingEntity.h"
#include "model/item/ItemStack.h"
#include "model/item/Inventory.h"
#include "viewmodel/PlayerController.h"
#include "viewmodel/PlayerModel.h"

class Player : public LivingEntity{
public:
    explicit Player(const Location& spawnLocation);
    Player(const Player& another) = delete;
    ~Player() override;
    [[nodiscard]] nlohmann::json serialize() const override;
    static std::unique_ptr<Player> deserialize(const nlohmann::json& json);
    [[nodiscard]] BoundingBox getBoundingBox() const override;
    [[nodiscard]] bool isFlying() const;
    void setFlying(bool flying);
private:
    void control();
    void updateModel();
    void jump();
    PlayerController* controller_;
    PlayerModel* model_;
    Task* task_;
    bool sprinting_;
    bool sneaking_;
    int currentSlot_;
    bool flying_;
    ItemStack cursor_;
    Inventory inventory_;
    Block *lastBreaking_;
    double breakingProgress_;
};


#endif //FLATCRAFT_PLAYER_H
