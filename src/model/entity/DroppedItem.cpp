//
// Created by Noy on 2023/7/12.
//

#include "model/entity/DroppedItem.h"
#include "model/event/events.h"

ItemStack *DroppedItem::getItemStack() const {
    return itemStack_.get();
}

void DroppedItem::setItemStack(std::unique_ptr<ItemStack> &itemStack) {
    itemStack_ = std::move(itemStack);
    ValueChangedNotification notification(this,Field::DROPPED_ITEM_ITEMSTACK,&itemStack_);
    EventManager::callEvent(notification);
}

long long DroppedItem::getTicksLived() const {
    return ticksLived_;
}

void DroppedItem::run() {
    Entity::run();
    ticksLived_++;
    if(ticksLived_>6000){
        remove();
    }
}

void DroppedItem::remove() {
    Entity::remove();

    ModelDestroyedNotification notification(this);
    EventManager::callEvent(notification);
}

