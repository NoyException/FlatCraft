//
// Created by Noy on 2023/7/12.
//

#include "model/entity/DroppedItem.h"

ItemStack *DroppedItem::getItemStack() const {
    return itemStack_.get();
}

void DroppedItem::setItemStack(std::unique_ptr<ItemStack> &itemStack) {
    itemStack_ = std::move(itemStack);
}

long long DroppedItem::getTicksLived() const {
    return ticksLived_;
}

