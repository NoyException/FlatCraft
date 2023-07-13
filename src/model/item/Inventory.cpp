//
// Created by Noy on 2023/7/9.
//

#include "model/item/Inventory.h"
#include "model/item/PlayerInventory.h"

Inventory::Inventory(int capacity) : capacity_(capacity), contents_(new std::unique_ptr<ItemStack>[capacity]) {}

Inventory::~Inventory() {
    delete[] contents_;
}

Inventory::Inventory(const nlohmann::json &json) :
capacity_(json.at("capacity").get<int>()), size_(json.at("size").get<int>()),
contents_(new std::unique_ptr<ItemStack>[capacity_]){
    const auto& contents = json.at("contents");
    for (int i = 0; i < capacity_; ++i){
        if(contents.contains(std::to_string(i)))
            contents_[i] = ItemStack::deserialize(contents.at(std::to_string(i)));
    }
}

std::unique_ptr<nlohmann::json> Inventory::serialize() const {
    auto json = std::make_unique<nlohmann::json>(nlohmann::json::initializer_list_t{
            {"type",static_cast<int>(getType())},
            {"capacity",capacity_},
            {"size",size_}});
    nlohmann::json contents;
    for (int i = 0; i < capacity_; ++i){
        if(contents_[i]!=nullptr){
            contents.emplace(std::to_string(i),*contents_[i]->serialize());
        }
    }
    json->emplace("contents",contents);
    return json;
}

void Inventory::validateIndex(int index) const {
    if(index<0 || index>=capacity_)
        throw std::out_of_range("index "+std::to_string(index)
        +" is out of range [0,"+std::to_string(capacity_)+")");
}

std::unique_ptr<Inventory> Inventory::deserialize(const nlohmann::json &json) {
    switch (static_cast<InventoryType>(json.at("type").get<int>())) {
        case InventoryType::BASE_INVENTORY:
            return std::make_unique<Inventory>(json);
        case InventoryType::PLAYER_INVENTORY:
            return std::make_unique<PlayerInventory>(json);
        default:
            return nullptr;
    }
}

bool Inventory::add(std::unique_ptr<ItemStack> &itemStack) {
    for(int i=0;i<capacity_;i++){
        if(contents_[i]==nullptr){
            size_++;
            contents_[i] = std::move(itemStack);
            return true;
        }
    }
    return false;
}

void Inventory::set(int index, std::unique_ptr<ItemStack> &&itemStack) {
    validateIndex(index);
    if(contents_[index]==nullptr && itemStack!=nullptr) size_++;
    if(contents_[index]!=nullptr && itemStack==nullptr) size_--;
    contents_[index] = std::move(itemStack);
}

ItemStack *Inventory::get(int index) const{
    validateIndex(index);
    return contents_[index].get();
}

std::unique_ptr <ItemStack> Inventory::remove(int index) {
    validateIndex(index);
    if(contents_[index]!=nullptr) size_--;
    return std::move(contents_[index]);
}

int Inventory::getSize() const {
    return size_;
}

int Inventory::getCapacity() const {
    return capacity_;
}

InventoryType Inventory::getType() const {
    return InventoryType::BASE_INVENTORY;
}


