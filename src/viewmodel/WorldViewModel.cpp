//
// Created by Noy on 2023/7/10.
//

#include "WorldViewModel.h"

WorldViewModel::WorldViewModel(Player *player) :
player_(player), ticks_(getWorld()->getTicks()), weather_(getWorld()->getWeather()) {}

World *WorldViewModel::getWorld() const {
    return player_->getWorld();
}

std::function<void(RefPtr<Vec2d>)> WorldViewModel::getBinderCameraPosition() {
    return [&](RefPtr<Vec2d> ptr){
        ptr.pointTo(cameraPosition_);
    };
}

std::function<void(RefPtr<Vec2d>)> WorldViewModel::getBinderLeftUpPosition() {
    return [&](RefPtr<Vec2d> ptr){
        ptr.pointTo(leftUpPosition_);
    };
}

std::function<void(RefPtr<MaterialMatrix>)> WorldViewModel::getBinderMaterialMatrix() {
    return [&](RefPtr<MaterialMatrix> ptr){
        ptr.pointTo(matrix_);
    };
}

std::function<void(RefPtr<long long>)> WorldViewModel::getBinderTicks() {
    return [&](RefPtr<long long> ptr){
        ptr.pointTo(ticks_);
    };
}

std::function<void(RefPtr<Weather>)> WorldViewModel::getBinderWeather() {
    return [&](RefPtr<Weather> ptr){
        ptr.pointTo(weather_);
    };
}

void WorldViewModel::setNotificationWeatherChanged(const std::function<void()> &notificationWeatherChanged) {
    notificationWeatherChanged_ = notificationWeatherChanged;
}

void WorldViewModel::onBound() {
    EventManager::registerListener<ValueChangedNotification<World>>(EventPriority::MONITOR,[&](ValueChangedNotification<World>* event){
        auto world = getWorld();
        if(event->getObject()==world){
            switch (event->getField()) {
                case Field::WORLD_TICKS:
                    ticks_ = event->getPayload<long long>();
                    break;
                case Field::WORLD_WEATHER:
                    weather_ = event->getPayload<Weather>();
                    notificationWeatherChanged_();
                    break;
                default:
                    break;
            }
        }
    });
    EventManager::registerListener<ValueChangedNotification<Entity>>(EventPriority::MONITOR,[&](ValueChangedNotification<Entity>* event){
        if(event->getObject() == player_ ){
            auto world = getWorld();
            if(event->getField()==Field::ENTITY_POSITION){
                std::unique_lock<std::shared_mutex> lock(matrix_.getSharedMutex());
                cameraPosition_ = player_->getLocation().toVec2d();
                leftUpPosition_ = Vec2d(cameraPosition_.getBlockX(),cameraPosition_.getBlockY()) +
                                  Vec2d((int)std::floor(-MaterialMatrix::MAX_COLUMN/2),(int)std::floor(MaterialMatrix::MAX_ROW*0.618));
                int x = leftUpPosition_.getBlockX();
                int y = leftUpPosition_.getBlockY()-1;
                for(int i = 0; i < MaterialMatrix::MAX_COLUMN; i++) {
                    for (int j = 0; j < MaterialMatrix::MAX_ROW; j++) {
                        for (int k = 0; k <= 1; k++) {
                            auto block = world->getBlock(x + i,y - j, k);
                            if (block == nullptr)
                                matrix_[i][j][k] = Material::BED_ROCK;
                            else
                                matrix_[i][j][k] = block->getMaterial();
                        }
                    }
                }
            }
        }
    });
}

//void WorldViewModel::setNotificationMaterialMatrixUpdated(const std::function<void()> &notificationMaterialMatrixUpdated) {
//    notificationMaterialMatrixUpdated_ = notificationMaterialMatrixUpdated;
//}
