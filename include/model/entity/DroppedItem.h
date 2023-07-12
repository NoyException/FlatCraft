//
// Created by Noy on 2023/7/12.
//

#ifndef FLATCRAFT_DROPPEDITEM_H
#define FLATCRAFT_DROPPEDITEM_H

#include "Entity.h"
#include "model/item/ItemStack.h"

class DroppedItem : public Entity {
public:
    DroppedItem(const Location& spawnLocation, std::unique_ptr<ItemStack>&& itemStack);
    [[nodiscard]] ItemStack* getItemStack() const;
    void setItemStack(std::unique_ptr<ItemStack> &&itemStack);
    [[nodiscard]] long long getTicksLived() const;
    void pickUpBy(Entity* entity);
    void remove() override;
    void notifyDisplayed() override;
protected:
    void run() override;
private:
    std::unique_ptr<ItemStack> itemStack_;
    long long ticksLived_;
};


#endif //FLATCRAFT_DROPPEDITEM_H
