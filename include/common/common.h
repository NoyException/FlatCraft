//
// Created by Noy on 2023/7/3.
//

#ifndef FLATCRAFT_COMMON_H
#define FLATCRAFT_COMMON_H

#include "precomp.h"

#include "json.hpp"
#include "Vec2d.h"
#include "BoundingBox.h"
#include "Material.h"
#include "EntityType.h"
#include "MaterialMatrix.h"
#include "InventorySlot.h"
#include "Weather.h"

enum class Key : int{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    SPACE,
    SHIFT,
    CTRL,
    LEFT_CLICK,
    RIGHT_CLICK,
};

enum class KeyState : bool{
    UP,
    DOWN,
};

#endif //FLATCRAFT_COMMON_H
