//
// Created by Noy on 2023/7/9.
//

#include "item/ItemStack.h"

ItemStack::ItemStack(Material material) : ItemStack(material, 1) {}

ItemStack::ItemStack(Material material, int amount) : item_(Item::of(material)),
meta_(ItemMeta::ofDefault(item_)), amount_(amount) {}

Item *ItemStack::getItem() const {
    return item_;
}

void ItemStack::setItem(Item *item) {
    if(item == nullptr) item = Item::of(Material::AIR);
    if(item!=item_){
        item_ = item;
        meta_ = ItemMeta::ofDefault(item);
    }
}

Material ItemStack::getMaterial() const {
    return item_->getMaterial();
}

void ItemStack::setMaterial(Material material) {
    setItem(Item::of(material));
}

const ItemMeta &ItemStack::getMeta() const {
    return meta_;
}

void ItemStack::setMeta(const ItemMeta &meta) {
    meta_ = meta;
}

int ItemStack::getAmount() const {
    return amount_;
}

void ItemStack::setAmount(int amount) {
    amount_ = amount;
}