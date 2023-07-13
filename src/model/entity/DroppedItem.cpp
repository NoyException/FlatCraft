//
// Created by Noy on 2023/7/12.
//

#include "model/FlatCraft.h"
#include "model/entity/DroppedItem.h"
#include "model/event/events.h"

DroppedItem::DroppedItem(std::unique_ptr<ItemStack> &&itemStack) :
Entity(), itemStack_(std::move(itemStack)), ticksLived_(0) {}

DroppedItem::DroppedItem(const nlohmann::json &json) : Entity(json),
itemStack_(ItemStack::deserialize(json.at("itemStack"))),
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
    notifyItemStackChanged();
}

long long DroppedItem::getTicksLived() const {
    return ticksLived_;
}

void DroppedItem::pickUpBy(Entity *entity) {
    auto player = dynamic_cast<Player*>(entity);
    if(player!=nullptr){
        if(!player->getInventory()->add(itemStack_))
            return;
    }
    ValueChangedNotification notification(this,Field::DROPPED_ITEM_STATE,1);
    EventManager::callEvent(notification);
    remove();
}

void DroppedItem::run() {
    Entity::run();
    //超时消失
    ticksLived_++;
    if(ticksLived_>6000){
        ValueChangedNotification notification(this,Field::DROPPED_ITEM_STATE,2);
        EventManager::callEvent(notification);
        remove();
        return;
    }
    //玩家捡起
    auto player = FlatCraft::getInstance()->getPlayer();
    if(player->getLocation().distanceSquared(location_)<1){
        pickUpBy(player);
        return;
    }
    //同类合并
    std::vector<DroppedItem*> items;
    getWorld()->getEntitiesNearby<DroppedItem>(items,location_.toVec2d(),1,[&](const DroppedItem& item){
        return item.getItemStack()->isSimilar(getItemStack());
    });
    int amount = itemStack_->getAmount();
    int maxAmount = itemStack_->getMaxAmount();
    for (const auto &item: items){
        if(item==this) continue;
        amount += item->itemStack_->getAmount();
        if(amount<maxAmount) item->remove();
        else{//amount>=maxAmount
            if(amount==maxAmount) item->remove();
            else{
                item->getItemStack()->setAmount(amount-maxAmount);
                item->notifyItemStackChanged();
                amount = maxAmount;
            }
            break;
        }
    }
    if(amount!=itemStack_->getAmount()){
        itemStack_->setAmount(amount);
        notifyItemStackChanged();
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

BoundingBox DroppedItem::getBoundingBox() const {
    BoundingBox aabb = Entity::getBoundingBox();
    aabb.expand(0.25,0,0.25,0.5);
    return aabb;
}

void DroppedItem::notifyItemStackChanged() {
    ValueChangedNotification notification(this,Field::DROPPED_ITEM_ITEMSTACK,&itemStack_);
    EventManager::callEvent(notification);
}


