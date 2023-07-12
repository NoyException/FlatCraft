//
// Created by Noy on 2023/7/9.
//

#include "model/item/Item.h"

Item::Item(Material material) : material_(material) {}

Material Item::getMaterial() const {
    return material_;
}

std::unordered_map<Material, Item> Item::byMaterial_;

void Item::registerAllItems() {
    std::vector<Material> materials;
    MaterialHelper::getAllMaterials(materials);
    for (const auto &item: materials){
        byMaterial_.emplace(item,Item(item));
    }
}

Item* Item::of(Material material) {
    auto it = byMaterial_.find(material);
    return it==byMaterial_.end() ? nullptr : &it->second;
}
