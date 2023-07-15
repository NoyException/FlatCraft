//
// Created by Noy on 2023/7/15.
//

#include "model/item/ShapedRecipe.h"

ShapedRecipe::ShapedRecipe(const nlohmann::json &json) :
        Recipe(std::make_unique<ItemStack>(MaterialHelper::getByName(json.at("result").get<std::string>()))){
    for (const auto &item: json.at("mapping").items()){
        mapping_.emplace(item.key().at(0),MaterialHelper::getByName(item.value().get<std::string>()));
    }
    for (const auto &s : json.at("shape")) {
        shape_.push_back(s);
    }
}

bool ShapedRecipe::match(const Material (&toMatch)[3][3]) const{
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if(getMaterial(i,j)!=toMatch[i][j])
                return false;
        }
    }
    return true;
}

Material ShapedRecipe::getMaterial(int i, int j) const {
    if(i<0 || i>= shape_.size()) return Material::AIR;
    if(j<0 || j>= shape_[i].length()) return Material::AIR;
    return getOrDefault(mapping_, shape_[i].at(j), Material::AIR);
}

