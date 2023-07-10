//
// Created by Noy on 2023/7/9.
//

#ifndef FLATCRAFT_ITEM_H
#define FLATCRAFT_ITEM_H

#include "common.h"

class Item {
public:
    static void registerAllItems();
    static Item* of(Material material);
    [[nodiscard]] Material getMaterial() const;
private:
    explicit Item(Material material);
    static std::unordered_map<Material, Item> byMaterial_;
    const Material material_;
};


#endif //FLATCRAFT_ITEM_H
