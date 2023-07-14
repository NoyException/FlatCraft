//
// Created by Noy on 2023/7/9.
//

#ifndef FLATCRAFT_ITEMMETA_H
#define FLATCRAFT_ITEMMETA_H

#include "common.h"
#include "Item.h"

class ItemMeta {
public:
    explicit ItemMeta(const nlohmann::json &json);
    [[nodiscard]] std::unique_ptr<nlohmann::json> serialize() const;
    virtual ~ItemMeta() = default;
    static std::unique_ptr<ItemMeta> ofDefault(Item* item);
    static std::unique_ptr<ItemMeta> ofDefault(Material material);
    [[nodiscard]] std::unique_ptr<ItemMeta> clone() const;
    [[nodiscard]] bool equals(const ItemMeta* another) const;
};


#endif //FLATCRAFT_ITEMMETA_H
