//
// Created by Noy on 2023/7/9.
//

#ifndef FLATCRAFT_ENTITYMODEL_H
#define FLATCRAFT_ENTITYMODEL_H

#include <mutex>
#include "EntityType.h"
#include "Vec2d.h"

class EntityModel {
public:
    explicit EntityModel(EntityType type);
    const EntityType type_;
    //是否正在被伤害，正在被伤害时实体应该发红
    bool damaged_;
    //是否正在燃烧
    bool burning_;
    //实体所在位置
    Vec2d position_;
    //实体移动速度
    Vec2d velocity_;
    //读取数据前使用std::lock_guard<std::mutex> lock(WorldModel::instance_.mtx_);
    std::mutex mtx_;
};


#endif //FLATCRAFT_ENTITYMODEL_H
