//
// Created by Noy on 2023/7/12.
//

#ifndef FLATCRAFT_MATERIALSTACK_H
#define FLATCRAFT_MATERIALSTACK_H


#include "Material.h"

struct MaterialStack {
    MaterialStack();
    MaterialStack(Material material, int amount);
    Material material_;
    int amount_;
};


#endif //FLATCRAFT_MATERIALSTACK_H
