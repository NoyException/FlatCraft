//
// Created by Noy on 2023/7/4.
//

#ifndef FLATCRAFT_PLAYER_H
#define FLATCRAFT_PLAYER_H

#include "common.h"
#include "model/entity/LivingEntity.h"
#include "model/item/ItemStack.h"
#include "model/item/PlayerInventory.h"

class Player : public LivingEntity{
public:
    friend class PlayerViewModel;
    Player();
    Player(const Player& another) = delete;
    ~Player() override = default;
    explicit Player(const nlohmann::json& json);
    [[nodiscard]] std::unique_ptr<nlohmann::json> serialize() const override;
    [[nodiscard]] BoundingBox getBoundingBox() const override;

    [[nodiscard]] int getCurrentSlot() const;

    void setCurrentSlot(int currentSlot);

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

    void tryToPlace(const Vec2d& position);

    void stopBreaking();

    [[nodiscard]] EntityType getType() const override;

    PlayerInventory* getInventory();

    [[nodiscard]] const ItemStack* getCursor() const;

    void setCursor(std::unique_ptr<ItemStack> &&cursor);

    [[nodiscard]] const ItemStack* getHand() const;

    void setHand(std::unique_ptr<ItemStack> &&);

    void clickSlot(int slotIndex);

    void respawn();
protected:
    void notifyJoinWorld(World *world) override;
    void notifyLeaveWorld(World *world) override;

    void onDie() override;

private:
    void control();
    //只能是-1 0 1
    int walkingDirection_;
    bool sprinting_;
    bool sneaking_;
    int currentSlot_;
    bool flying_;
    std::unique_ptr<ItemStack> cursor_;
    std::unique_ptr<PlayerInventory> inventory_;
    Block *lastBreaking_;
    double breakingProgress_;
};


#endif //FLATCRAFT_PLAYER_H
