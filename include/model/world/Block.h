//
// Created by Noy on 2023/7/3.
//


#ifndef FLATCRAFT_BLOCK_H
#define FLATCRAFT_BLOCK_H

#include "common.h"
#include "Material.h"
#include "Location.h"
#include "BlockData.h"

enum class BlockFace : unsigned char{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    FORWARD,
    BACKWARD
};

class Block {
public:
    Block(Material material, const Location& location, bool front);
    [[nodiscard]] nlohmann::json serialize() const;
    static Block deserialize(Location&& location, bool front, const nlohmann::json& json);
    [[nodiscard]] Material getMaterial() const;
    void setMaterial(const Material& material);
    [[nodiscard]] Location getLocation() const;
    [[nodiscard]] bool isFront() const;
    [[nodiscard]] BoundingBox getBoundingBox() const;
private:
    Material material_;
    Location location_;
    bool front_;
    std::optional<BlockData> data_;
};


#endif //FLATCRAFT_BLOCK_H
