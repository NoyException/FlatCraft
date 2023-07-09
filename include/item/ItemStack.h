//
// Created by Noy on 2023/7/9.
//

#ifndef FLATCRAFT_ITEMSTACK_H
#define FLATCRAFT_ITEMSTACK_H

#include "Item.h"
#include "ItemMeta.h"

class ItemStack {
public:
    explicit ItemStack(Material material);
    ItemStack(Material material, int amount);

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
    std::unique_ptr<ItemMeta> meta_;
    int amount_;
};


#endif //FLATCRAFT_ITEMSTACK_H
