//
// Created by Noy on 2023/7/10.
//

#ifndef FLATCRAFT_WORLDVIEWMODEL_H
#define FLATCRAFT_WORLDVIEWMODEL_H

#include "model/entity/player/Player.h"
#include "model/world/World.h"

class WorldViewModel {
public:
    explicit WorldViewModel(Player *player);
    static const int MAX_ROW = 28;
    static const int MAX_COLUMN = 42;
    friend class Binder;
    [[nodiscard]] World* getWorld() const;
    void updateMaterials(Material materials[][28][2], const Vec2d& lastLeftUpPosition) const;
    [[nodiscard]] Vec2d getCameraPosition() const;
    [[nodiscard]] Vec2d getLeftUpPosition() const;
    [[nodiscard]] long long getTicks() const;
private:
    Player* player_;
//    std::function<void(Weather)> weatherUpdater_;
};


#endif //FLATCRAFT_WORLDVIEWMODEL_H
