//
// Created by Noy on 2023/7/12.
//

#include "model/FlatCraft.h"
#include "model/entity/DroppedItem.h"
#include "model/event/events.h"

DroppedItem::DroppedItem(const Location& spawnLocation, std::unique_ptr<ItemStack> &&itemStack) :
Entity(spawnLocation), itemStack_(std::move(itemStack)), ticksLived_(0) {}

ItemStack *DroppedItem::getItemStack() const {
    return itemStack_.get();
}

void DroppedItem::setItemStack(std::unique_ptr<ItemStack> &&itemStack) {
    itemStack_ = std::move(itemStack);
    ValueChangedNotification notification(this,Field::DROPPED_ITEM_ITEMSTACK,&itemStack_);
    EventManager::callEvent(notification);
}

long long DroppedItem::getTicksLived() const {
    return ticksLived_;
}

void DroppedItem::pickUpBy(Entity *entity) {
    ValueChangedNotification notification(this,Field::DROPPED_ITEM_STATE,1);
    EventManager::callEvent(notification);
    remove();
}

void DroppedItem::run() {
    Entity::run();
    ticksLived_++;
    if(ticksLived_>6000){
        ValueChangedNotification notification(this,Field::DROPPED_ITEM_STATE,2);
        EventManager::callEvent(notification);
        remove();
    }
    auto player = FlatCraft::getInstance()->getPlayer();
    if(player->getLocation().distanceSquared(location_)<1){
        pickUpBy(player);
    }
}

void DroppedItem::remove() {
    Entity::remove();
    ModelDestroyedNotification notification(this);
    EventManager::callEvent(notification);
}

void DroppedItem::notifyDisplayed() {
    ModelCreatedNotification notification(this);
    EventManager::callEvent(notification);
}

