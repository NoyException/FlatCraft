//
// Created by Noy on 2023/7/9.
//

#include "model/item/ItemStack.h"

ItemStack::ItemStack(Material material, int amount) :
ItemStack(material, amount, ItemMeta::ofDefault(material)){}

ItemStack::ItemStack(Material material, int amount, std::unique_ptr<ItemMeta>&& meta) :
item_(Item::of(material)), amount_(amount), meta_(std::move(meta)){}

ItemStack::ItemStack(const nlohmann::json &json) :
ItemStack(static_cast<Material>(json.at("material").get<int>()),
          json.at("amount").get<int>(),
          std::make_unique<ItemMeta>(json.at("meta"))){}

std::unique_ptr<nlohmann::json> ItemStack::serialize() const {
    return std::make_unique<nlohmann::json>(nlohmann::json::initializer_list_t{
            {"material",static_cast<int>(item_->getMaterial())},
            {"amount",amount_},
            {"meta",*meta_->serialize()}});
}

std::unique_ptr<ItemStack> ItemStack::deserialize(const nlohmann::json &json) {
    return std::make_unique<ItemStack>(json);
}

std::unique_ptr<ItemStack> ItemStack::clone() const {
    auto copy = std::make_unique<ItemStack>(getMaterial(),amount_);
    copy->meta_ = meta_->clone();
    return std::move(copy);
}

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

ItemMeta* ItemStack::getMeta() const {
    return meta_.get();
}

void ItemStack::setMeta(std::unique_ptr<ItemMeta>&& meta) {
    meta_ = std::move(meta);
}

int ItemStack::getAmount() const {
    return amount_;
}

void ItemStack::setAmount(int amount) {
    amount_ = amount;
    if(amount_<=0){
        setMaterial(Material::AIR);
        amount_ = 1;
    }
}

MaterialStack ItemStack::toMaterialStack() const {
    return MaterialStack{getMaterial(),amount_};
}

bool ItemStack::isSimilar(const ItemStack *another) const {
    return item_ == another->item_ && meta_->equals(another->meta_.get());
}

bool ItemStack::equals(const ItemStack *another) const {
    return isSimilar(another) && amount_==another->amount_;
}

int ItemStack::getMaxAmount() const {
    return MaterialHelper::getInfo(getMaterial())->maxStacks_;
}