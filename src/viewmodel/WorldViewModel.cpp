//
// Created by Noy on 2023/7/10.
//

#include "WorldViewModel.h"

WorldViewModel::WorldViewModel(Player *player) : player_(player) {
    EventManager::registerListener(EventType::VALUE_CHANGED_NOTIFICATION, EventPriority::MONITOR,[&](EventInstance *event){
        auto e = dynamic_cast<ValueChangedNotification<World>*>(event);
        auto world = getWorld();
        if(e!= nullptr){
            if(e->getObject()==world){
                switch (e->getField()) {
                    case Field::WORLD_TICKS:
                        ticks_ = e->getNewValue<long long>();
                        break;
                    case Field::WORLD_WEATHER:
                        weather_ = e->getNewValue<Weather>();
                        notificationWeatherChanged_();
                        break;
                    default:
                        break;
                }
            }
        }
        else{
            auto e2 = dynamic_cast<ValueChangedNotification<Entity>*>(event);
            if(e2!= nullptr && e2->getObject() == player_ ){
                if(e2->getField()==Field::ENTITY_POSITION){
                    cameraPosition_ = player_->getLocation().toVec2d();
                    Vec2d leftUpPosition(cameraPosition_.getBlockX(),cameraPosition_.getBlockY());
                    leftUpPosition.add((int)std::floor(-MaterialMatrix::MAX_COLUMN/2),(int)std::floor(MaterialMatrix::MAX_ROW*0.618));
                    int x = leftUpPosition.getBlockX();
                    int y = leftUpPosition.getBlockY()-1;
                    for(int i = 0; i < MaterialMatrix::MAX_COLUMN; i++) {
                        for (int j = 0; j < MaterialMatrix::MAX_ROW; j++) {
                            for (int k = 0; k <= 1; k++) {
                                auto block = world->getBlock(x + i,y - j - 1, k);
                                if (block == nullptr)
                                    matrix_[i][j][k] = Material::BED_ROCK;
                                else
                                    matrix_[i][j][k] = block->getMaterial();
                            }
                        }
                    }
                }
            }
        }
    });
}

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

void WorldViewModel::update() {
    auto world = getWorld();
    Vec2d cameraPosition = player_->getLocation().toVec2d();
    Vec2d leftUpPosition(cameraPosition.getBlockX(),cameraPosition.getBlockY());
    leftUpPosition.add((int)std::floor(-MaterialMatrix::MAX_COLUMN/2),(int)std::floor(MaterialMatrix::MAX_ROW*0.618));

}

//void WorldViewModel::setNotificationMaterialMatrixUpdated(const std::function<void()> &notificationMaterialMatrixUpdated) {
//    notificationMaterialMatrixUpdated_ = notificationMaterialMatrixUpdated;
//}
