//
// Created by Noy on 2023/7/3.
//

#ifndef FLATCRAFT_COMMON_H
#define FLATCRAFT_COMMON_H

#include "precomp.h"

#include "RefPtr.h"
#include "Random.h"
#include "json.hpp"
#include "Vec2d.h"
#include "BoundingBox.h"
#include "Material.h"
#include "EntityType.h"
#include "MaterialMatrix.h"
#include "MaterialStack.h"
#include "Weather.h"
#include "MultiDimensionalArray.h"

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
    ESC,
    OPENINVEMTORY
};

enum class KeyState : bool{
    UP,
    DOWN,
};


#endif //FLATCRAFT_COMMON_H
