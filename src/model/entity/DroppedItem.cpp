//
// Created by Noy on 2023/7/12.
//

#include "model/FlatCraft.h"
#include "model/entity/DroppedItem.h"
#include "model/event/events.h"

DroppedItem::DroppedItem(std::unique_ptr<ItemStack> &&itemStack) :
Entity(), itemStack_(std::move(itemStack)), ticksLived_(0) {}

DroppedItem::DroppedItem(const nlohmann::json &json) : Entity(json),
itemStack_(std::make_unique<ItemStack>(json.at("itemStack"))),
ticksLived_(json.at("ticksLived").get<long long>()){}

std::unique_ptr<nlohmann::json> DroppedItem::serialize() const {
    auto json = Entity::serialize();
    json->emplace("itemStack",*itemStack_->serialize());
    json->emplace("ticksLived",ticksLived_);
    return json;
}

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

void DroppedItem::notifyJoinWorld(World *world) {
    Entity::notifyJoinWorld(world);
    ModelCreatedNotification notification(this);
    EventManager::callEvent(notification);
}

void DroppedItem::notifyLeaveWorld(World *world) {
    Entity::notifyLeaveWorld(world);
    ModelDestroyedNotification notification(this);
    EventManager::callEvent(notification);
}

EntityType DroppedItem::getType() const {
    return EntityType::DROPPED_ITEM;
}


