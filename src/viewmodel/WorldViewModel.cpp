//
// Created by Noy on 2023/7/10.
//

#include "WorldViewModel.h"
#include "model/FlatCraft.h"

WorldViewModel::WorldViewModel(Player *player) : player_(player) {
    EventManager::registerListener(EventType::WORLD_WEATHER_CHANGE_EVENT, EventPriority::MONITOR,
                                   [&](EventInstance *event){
                                       auto e = dynamic_cast<WorldWeatherChangeEvent*>(event);
                                       if(e->isCanceled()) return;
                                       if(e->getWorld()==getWorld()){
                                           FlatCraft::getInstance()->getScheduler()->runTask([&](){
                                               notificationWeatherChanged_();
                                           });
                                       }
                                   });
}

World *WorldViewModel::getWorld() const {
    return player_->getWorld();
}

std::function<Vec2d()> WorldViewModel::getBinderCameraPosition() {
    return [&](){
        return player_->getLocation().toVec2d();
    };
}

std::function<Vec2d()> WorldViewModel::getBinderLeftUpPosition() {
    return [&](){
        Vec2d cameraPosition = player_->getLocation().toVec2d();
        Vec2d leftUpPosition(cameraPosition.getBlockX(),cameraPosition.getBlockY());
        leftUpPosition.add((int)std::floor(-MaterialMatrix::MAX_COLUMN/2),(int)std::floor(MaterialMatrix::MAX_ROW*0.618));
        return leftUpPosition;
    };
}

std::function<void(MaterialMatrix&)> WorldViewModel::getBinderMaterialMatrix() {
    return [&](MaterialMatrix &matrix){
        auto world = getWorld();
        Vec2d cameraPosition = player_->getLocation().toVec2d();
        Vec2d leftUpPosition(cameraPosition.getBlockX(),cameraPosition.getBlockY());
        leftUpPosition.add((int)std::floor(-MaterialMatrix::MAX_COLUMN/2),(int)std::floor(MaterialMatrix::MAX_ROW*0.618));
        int x = leftUpPosition.getBlockX();
        int y = leftUpPosition.getBlockY()-1;
        for(int i = 0; i < MaterialMatrix::MAX_COLUMN; i++) {
            for (int j = 0; j < MaterialMatrix::MAX_ROW; j++) {
                for (int k = 0; k <= 1; k++) {
                    auto block = world->getBlock(x + i,y - j - 1, k);
                    if (block == nullptr)
                        matrix[i][j][k] = Material::BED_ROCK;
                    else
                        matrix[i][j][k] = block->getMaterial();
                }
            }
        }
    };
}

std::function<double()> WorldViewModel::getBinderTicks() {
    return [&](){
        return getWorld()->getTicks();
    };
}

std::function<Weather()> WorldViewModel::getBinderWeather() {
    return [&](){
        return getWorld()->getWeather();
    };
}

void WorldViewModel::setNotificationWeatherChanged(const std::function<void()> &notificationWeatherChanged) {
    notificationWeatherChanged_ = notificationWeatherChanged;
}

//void WorldViewModel::setNotificationMaterialMatrixUpdated(const std::function<void()> &notificationMaterialMatrixUpdated) {
//    notificationMaterialMatrixUpdated_ = notificationMaterialMatrixUpdated;
//}
