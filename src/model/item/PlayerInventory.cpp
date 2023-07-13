//
// Created by Noy on 2023/7/13.
//

#include "model/item/PlayerInventory.h"
#include "model/event/events.h"

int* PlayerInventory::ADD_ORDER = nullptr;

PlayerInventory::PlayerInventory() : Inventory(46) {}

PlayerInventory::PlayerInventory(const nlohmann::json &json) : Inventory(json) {}

bool PlayerInventory::add(std::unique_ptr<ItemStack> &itemStack) {
    if(ADD_ORDER==nullptr){
        ADD_ORDER = new int[36];
        for(int i=0;i<9;i++){
            ADD_ORDER[i] = 36+i;
        }
        for(int i=0;i<27;i++){
            ADD_ORDER[i+9] = 9+i;
        }
    }
    for(int i=0;i<36;i++){
        if(contents_[ADD_ORDER[i]]==nullptr){
            size_++;
            contents_[ADD_ORDER[i]] = std::move(itemStack);
            ValueChangedNotification notification(this,Field::PLAYER_INVENTORY,i);
            EventManager::callEvent(notification);
            return true;
        }
    }
    return false;
}

void PlayerInventory::set(int index, std::unique_ptr<ItemStack> &&itemStack) {
    Inventory::set(index, std::move(itemStack));
    ValueChangedNotification notification(this,Field::PLAYER_INVENTORY,index);
    EventManager::callEvent(notification);
}

std::unique_ptr<ItemStack> PlayerInventory::remove(int index) {
    auto res = Inventory::remove(index);
    ValueChangedNotification notification(this,Field::PLAYER_INVENTORY,index);
    EventManager::callEvent(notification);
    return res;
}


InventoryType PlayerInventory::getType() const {
    return InventoryType::PLAYER_INVENTORY;
}