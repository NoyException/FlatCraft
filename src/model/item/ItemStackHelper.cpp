//
// Created by Noy on 2023/7/13.
//

#include "model/item/ItemStackHelper.h"

bool ItemStackHelper::isAir(std::unique_ptr<ItemStack> &itemStack) {
    return itemStack==nullptr || MaterialHelper::isAir(itemStack->getMaterial()) || itemStack->getAmount()<=0;
}

bool ItemStackHelper::isAir(const ItemStack *itemStack) {
    return itemStack==nullptr || MaterialHelper::isAir(itemStack->getMaterial()) || itemStack->getAmount()<=0;
}

bool ItemStackHelper::isSimilar(std::unique_ptr<ItemStack> &a, std::unique_ptr<ItemStack> &b) {
    bool aAir = isAir(a);
    bool bAir = isAir(b);
    if(aAir && bAir) return true;
    if(!aAir && !bAir) return a->isSimilar(b.get());
    return false;
}

bool ItemStackHelper::isSimilar(const ItemStack *a, ItemStack *b) {
    bool aAir = isAir(a);
    bool bAir = isAir(b);
    if(aAir && bAir) return true;
    if(!aAir && !bAir) return a->isSimilar(b);
    return false;
}
