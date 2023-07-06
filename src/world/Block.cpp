//
// Created by Noy on 2023/7/3.
//

#include "world/Block.h"

Material Block::getMaterial() const {
    return material_;
}

void Block::setMaterial(const Material &material) {
    material_ = material;
}

Location Block::getLocation() const {
    return location_;
}

Block::Block(Material material, const Location& location) : material_(material), location_(location) {

}

nlohmann::json Block::serialize() const {
    nlohmann::json json({{"material", static_cast<int>(material_)}});
    if(data_.has_value())
        json.emplace("data",data_.value().serialize());
    return std::move(json);
}

Block Block::deserialize(Location&& location, const nlohmann::json &json) {
    Block block(static_cast<Material>(json.at("material").get<int>()),location);
    if(json.contains("data"))
        block.data_ = BlockData::deserialize(json.at("data"));
    return std::move(block);
}
