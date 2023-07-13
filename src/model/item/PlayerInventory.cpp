//
// Created by Noy on 2023/7/13.
//

#include "model/item/PlayerInventory.h"

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
            return true;
        }
    }
    return false;
}

InventoryType PlayerInventory::getType() const {
    return InventoryType::PLAYER_INVENTORY;
}
