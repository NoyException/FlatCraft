//
// Created by Noy on 2023/7/13.
//

#ifndef FLATCRAFT_ITEMSTACKHELPER_H
#define FLATCRAFT_ITEMSTACKHELPER_H

#include "common.h"
#include "ItemStack.h"

class ItemStackHelper {
public:
    static bool is(const std::unique_ptr<ItemStack>& itemStack, Material material);
    static bool is(const ItemStack* itemStack, Material material);
    static bool isAir(const std::unique_ptr<ItemStack>& itemStack);
    static bool isAir(const ItemStack* itemStack);
    static bool isSimilar(const std::unique_ptr<ItemStack>& a, std::unique_ptr<ItemStack>& b);
    static bool isSimilar(const ItemStack* a, ItemStack* b);
};


#endif //FLATCRAFT_ITEMSTACKHELPER_H
