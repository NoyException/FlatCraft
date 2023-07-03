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
