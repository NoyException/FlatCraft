//
// Created by Noy on 2023/7/3.
//


#ifndef FLATCRAFT_BLOCK_H
#define FLATCRAFT_BLOCK_H

#include "common.h"

class Block {
public:
    [[nodiscard]] Material getMaterial() const;
    void setMaterial(const Material& material);
    [[nodiscard]] Location getLocation() const;
private:
    Material material_;
    Location location_;
};


#endif //FLATCRAFT_BLOCK_H
