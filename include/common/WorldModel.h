//
// Created by Noy on 2023/7/7.
//

#ifndef FLATCRAFT_WORLDMODEL_H
#define FLATCRAFT_WORLDMODEL_H

#include "Material.h"
#include "Vec2d.h"
#include <mutex>

enum class Weather : int{
    CLEAR,
    RAIN,
    THUNDERSTORM
};

class WorldModel {
public:
    static const int MAX_ROW = 26;
    static const int MAX_COLUMN = 42;
    Material materials_[MAX_COLUMN][MAX_ROW][2];
    Vec2d leftUpPosition_;
    Vec2d cameraPosition_;
    long long ticks_;
    Weather weather_;
    //读取数据前使用std::lock_guard<std::mutex> lock(WorldModel::instance_.mtx_);
    std::mutex mtx_;
    static WorldModel instance_;
};

#endif //FLATCRAFT_WORLDMODEL_H
