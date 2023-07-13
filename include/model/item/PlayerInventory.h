//
// Created by Noy on 2023/7/13.
//

#ifndef FLATCRAFT_PLAYERINVENTORY_H
#define FLATCRAFT_PLAYERINVENTORY_H

#include "Inventory.h"

class PlayerInventory : public Inventory {
public:
    PlayerInventory();

    explicit PlayerInventory(const nlohmann::json &json);

    bool add(std::unique_ptr<ItemStack> &itemStack) override;

    void set(int index, std::unique_ptr<ItemStack> &&itemStack) override;

    std::unique_ptr<ItemStack> remove(int index) override;

    [[nodiscard]] InventoryType getType() const override;

private:
    static int* ADD_ORDER;
};


#endif //FLATCRAFT_PLAYERINVENTORY_H
