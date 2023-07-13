//
// Created by Noy on 2023/7/10.
//

#ifndef FLATCRAFT_WORLDVIEWMODEL_H
#define FLATCRAFT_WORLDVIEWMODEL_H

#include "common.h"
#include "ViewModel.h"
#include "model/entity/player/Player.h"
#include "model/world/World.h"

class WorldViewModel : public ViewModel{
public:
    explicit WorldViewModel(Player *player);

    std::function<void(RefPtr<Vec2d>)> getBinderCameraPosition();
    std::function<void(RefPtr<Vec2d>)> getBinderLeftUpPosition();
    std::function<void(RefPtr<MaterialMatrix>)> getBinderMaterialMatrix();
    std::function<void(RefPtr<long long>)> getBinderTicks();
    std::function<void(RefPtr<Weather>)> getBinderWeather();

    void setNotificationWeatherChanged(const std::function<void()> &notificationWeatherChanged);
    //传入的lambda将在matrix需要更新时调用
//    void setNotificationMaterialMatrixUpdated(const std::function<void()> &notificationMaterialMatrixUpdated);
protected:
    void onBound() override;

private:
    [[nodiscard]] World* getWorld() const;
    Player* player_;

    Vec2d cameraPosition_;
    Vec2d leftUpPosition_;
    MaterialMatrix matrix_;
    long long ticks_;
    Weather weather_;

    std::function<void()> notificationWeatherChanged_;
//    std::function<void()> notificationMaterialMatrixUpdated_;
};


#endif //FLATCRAFT_WORLDVIEWMODEL_H
