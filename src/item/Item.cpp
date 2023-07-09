//
// Created by Noy on 2023/7/9.
//

#include "item/Item.h"

Item::Item(Material material) : material_(material) {}

Material Item::getMaterial() const {
    return material_;
}

std::unordered_map<Material, Item> Item::byMaterial_;

void Item::registerAllItems() {
    byMaterial_.emplace(Material::AIR,Item(Material::AIR));
    byMaterial_.emplace(Material::DIRT,Item(Material::DIRT));
}

Item* Item::of(Material material) {
    auto it = byMaterial_.find(material);
    return it==byMaterial_.end() ? nullptr : &it->second;
}
