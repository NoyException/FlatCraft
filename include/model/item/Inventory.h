//
// Created by Noy on 2023/7/9.
//

#ifndef FLATCRAFT_INVENTORY_H
#define FLATCRAFT_INVENTORY_H

#include "common.h"
#include "ItemStack.h"

enum class InventoryType : int{
    BASE_INVENTORY,
    PLAYER_INVENTORY,
    CHEST_INVENTORY
};

class Inventory {
public:
    explicit Inventory(int capacity);
    virtual ~Inventory();
    explicit Inventory(const nlohmann::json& json);
    [[nodiscard]] virtual std::unique_ptr<nlohmann::json> serialize() const;
    static std::unique_ptr<Inventory> deserialize(const nlohmann::json& json);

    [[nodiscard]] ItemStack* get(int index) const;
    virtual bool add(std::unique_ptr<ItemStack>& itemStack);
    virtual void set(int index, std::unique_ptr<ItemStack>&& itemStack);
    virtual std::unique_ptr<ItemStack> remove(int index);
    [[nodiscard]] int getSize() const;
    [[nodiscard]] int getCapacity() const;
    [[nodiscard]] virtual InventoryType getType() const;
protected:
    void validateIndex(int index) const;
    int size_ = 0;
    int capacity_;
    std::unique_ptr<ItemStack> *contents_;
};


#endif //FLATCRAFT_INVENTORY_H
