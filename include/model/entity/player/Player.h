//
// Created by Noy on 2023/7/4.
//

#ifndef FLATCRAFT_PLAYER_H
#define FLATCRAFT_PLAYER_H

#include "common.h"
#include "model/entity/LivingEntity.h"
#include "model/item/ItemStack.h"
#include "model/item/Inventory.h"

class Player : public LivingEntity{
public:
    explicit Player(const Location& spawnLocation);
    Player(const Player& another) = delete;
    ~Player() override;
    explicit Player(const nlohmann::json& json);
    static std::unique_ptr<Player> deserialize(const nlohmann::json& json);
    [[nodiscard]] std::unique_ptr<nlohmann::json> serialize() const override;
    [[nodiscard]] BoundingBox getBoundingBox() const override;

    [[nodiscard]] int getCurrentSlot() const;

    [[nodiscard]] double getBreakingProgress() const;

    [[nodiscard]] int getWalkingDirection() const;

    void setWalkingDirection(int walkingDirection);

    [[nodiscard]] bool isSprinting() const;

    void setSprinting(bool sprinting);

    [[nodiscard]] bool isSneaking() const;

    void setSneaking(bool sneaking);

    [[nodiscard]] bool isFlying() const;

    void setFlying(bool flying);

    void jump();

    void tryToBreak(const Vec2d& position);

    void stopBreaking();

    friend class PlayerViewModel;
private:
    void control();
    //只能是-1 0 1
    int walkingDirection_;
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
