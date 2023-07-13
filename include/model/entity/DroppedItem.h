//
// Created by Noy on 2023/7/12.
//

#ifndef FLATCRAFT_DROPPEDITEM_H
#define FLATCRAFT_DROPPEDITEM_H

#include "Entity.h"
#include "model/item/ItemStack.h"

class DroppedItem : public Entity {
public:
    explicit DroppedItem(std::unique_ptr<ItemStack>&& itemStack);
    explicit DroppedItem(const nlohmann::json& json);
    [[nodiscard]] std::unique_ptr<nlohmann::json> serialize() const override;
    [[nodiscard]] ItemStack* getItemStack() const;
    void setItemStack(std::unique_ptr<ItemStack> &&itemStack);
    [[nodiscard]] long long getTicksLived() const;
    void pickUpBy(Entity* entity);
    [[nodiscard]] EntityType getType() const override;
//    void notifyDisplayed() override;
protected:
    void notifyJoinWorld(World *world) override;
    void notifyLeaveWorld(World *world) override;
    void run() override;
private:
    std::unique_ptr<ItemStack> itemStack_;
    long long ticksLived_;
};


#endif //FLATCRAFT_DROPPEDITEM_H
