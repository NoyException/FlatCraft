//
// Created by Noy on 2023/7/9.
//

#include "model/item/ItemMeta.h"


ItemMeta::ItemMeta(const nlohmann::json &json) {}

std::unique_ptr<nlohmann::json> ItemMeta::serialize() const {
    return std::make_unique<nlohmann::json>(nlohmann::json::initializer_list_t{"null"});
}

std::unique_ptr<ItemMeta> ItemMeta::ofDefault(Item *item) {
    return {};
}

std::unique_ptr<ItemMeta> ItemMeta::ofDefault(Material material) {
    return {};
}
