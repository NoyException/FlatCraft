//
// Created by Noy on 2023/7/9.
//

#ifndef FLATCRAFT_ITEMSTACK_H
#define FLATCRAFT_ITEMSTACK_H

#include "Item.h"
#include "ItemMeta.h"

class ItemStack {
public:
    explicit ItemStack(Material material, int amount = 1);
    ItemStack(Material material, int amount, std::unique_ptr<ItemMeta> meta);
    explicit ItemStack(const nlohmann::json &json);
    [[nodiscard]] std::unique_ptr<nlohmann::json> serialize() const;

    [[nodiscard]] Item *getItem() const;
    void setItem(Item *item);

    [[nodiscard]] Material getMaterial() const;
    void setMaterial(Material material);

    [[nodiscard]] ItemMeta* getMeta() const;
    void setMeta(std::unique_ptr<ItemMeta> meta);

    [[nodiscard]] int getAmount() const;
    void setAmount(int amount);

private:
    Item* item_;
    int amount_;
    std::unique_ptr<ItemMeta> meta_;
};


#endif //FLATCRAFT_ITEMSTACK_H
