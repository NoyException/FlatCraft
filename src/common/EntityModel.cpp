//
// Created by Noy on 2023/7/9.
//

#include "EntityModel.h"

EntityModel::EntityModel(EntityType type) : type_(type), damaged_(false), burning_(false),
position_(0,64), velocity_(){

}
