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

template<class A, class B>
std::unique_ptr<A> dynamic_unique_cast(std::unique_ptr<B>&& p){
    static_assert(std::is_convertible<A*, B*>::value, "A must be convertible to B");
    B* b = p.release();
    A* a = dynamic_cast<A*>(b);
    if(a == nullptr){
        delete b;
        return nullptr;
    }
    return std::unique_ptr<A>(a);
}


#endif //FLATCRAFT_COMMON_H
