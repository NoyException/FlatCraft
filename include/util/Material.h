//
// Created by Noy on 2023/7/3.
//

#ifndef FLATCRAFT_MATERIAL_H
#define FLATCRAFT_MATERIAL_H

enum class Material : int {
    AIR,
    DIRT,
    GRASS,
    STONE,
    BED_ROCK,
    WATER,
};

namespace MaterialHelper{
    bool isOccluded(Material material);
    bool isSolid(Material material);
    bool isAir(Material material);
}

#endif //FLATCRAFT_MATERIAL_H
