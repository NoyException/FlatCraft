//
// Created by Noy on 2023/7/3.
//

#include "model/world/Block.h"

Block::Block(Material material, const Location& location, bool front) :
        material_(material), location_(location), front_(front) {

}

Material Block::getMaterial() const {
    return material_;
}

void Block::setMaterial(const Material &material) {
    material_ = material;
}

Location Block::getLocation() const {
    return location_;
}

nlohmann::json Block::serialize() const {
    nlohmann::json json({{"material", static_cast<int>(material_)}});
    if(data_.has_value())
        json.emplace("data",data_.value().serialize());
    return std::move(json);
}

Block Block::deserialize(Location&& location, bool front, const nlohmann::json &json) {
    Block block(static_cast<Material>(json.at("material").get<int>()),location,front);
    if(json.contains("data"))
        block.data_ = BlockData::deserialize(json.at("data"));
    return std::move(block);
}

bool Block::isFront() const {
    return front_;
}

BoundingBox Block::getBoundingBox() const {
    double x = location_.getBlockX();
    double y = location_.getBlockY();
    if(MaterialHelper::isAir(material_)) return {x,y,x,y};
    return {x,y,x+1,y+1};
}