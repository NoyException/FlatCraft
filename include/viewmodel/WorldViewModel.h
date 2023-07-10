//
// Created by Noy on 2023/7/10.
//

#ifndef FLATCRAFT_WORLDVIEWMODEL_H
#define FLATCRAFT_WORLDVIEWMODEL_H

#include "common.h"
#include "model/entity/player/Player.h"
#include "model/world/World.h"

class WorldViewModel {
public:
    explicit WorldViewModel(Player *player);

    std::function<Vec2d()> getBinderCameraPosition();
    std::function<Vec2d()> getBinderLeftUpPosition();
    std::function<void(MaterialMatrix&)> getBinderMaterialMatrix();
    std::function<double()> getBinderTicks();
    std::function<Weather()> getBinderWeather();

    void setNotificationWeatherChanged(const std::function<void()> &notificationWeatherChanged);
    //传入的lambda将在matrix需要更新时调用
//    void setNotificationMaterialMatrixUpdated(const std::function<void()> &notificationMaterialMatrixUpdated);
private:
    [[nodiscard]] World* getWorld() const;
    Player* player_;
    std::function<void()> notificationWeatherChanged_;
//    std::function<void()> notificationMaterialMatrixUpdated_;
};


#endif //FLATCRAFT_WORLDVIEWMODEL_H
