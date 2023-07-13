//
// Created by Noy on 2023/7/12.
//

#include "MaterialStack.h"

MaterialStack::MaterialStack() : MaterialStack(Material::AIR,1) {}

MaterialStack::MaterialStack(Material material, int amount) : material_(material), amount_(amount){}
