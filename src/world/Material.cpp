//
// Created by Noy on 2023/7/6.
//

#include "world/Material.h"

namespace MaterialHelper{
    bool isOccluded(Material material){
        switch (material) {
            case Material::GRASS:
            case Material::DIRT:
            case Material::STONE:
            case Material::BED_ROCK:
                return true;
            default:
                return false;
        }
    }

    bool isSolid(Material material){
        switch (material) {
            case Material::GRASS:
            case Material::DIRT:
            case Material::STONE:
            case Material::BED_ROCK:
                return true;
            default:
                return false;
        }
    }

    bool isAir(Material material){
        switch (material) {
            case Material::AIR:
                return true;
            default:
                return false;
        }
    }
}