//
// Created by Noy on 2023/7/3.
//


#ifndef FLATCRAFT_BLOCK_H
#define FLATCRAFT_BLOCK_H

#include "common.h"
#include "Material.h"
#include "Location.h"
#include "BlockData.h"

class Block {
public:
    Block(Material material, const Location& location);
    [[nodiscard]] nlohmann::json serialize() const;
    static Block deserialize(Location&& location, const nlohmann::json& json);
    [[nodiscard]] Material getMaterial() const;
    void setMaterial(const Material& material);
    [[nodiscard]] Location getLocation() const;
private:
    Material material_;
    Location location_;
    std::optional<BlockData> data_;
};


#endif //FLATCRAFT_BLOCK_H
