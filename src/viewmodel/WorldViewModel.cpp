//
// Created by Noy on 2023/7/10.
//

#include "WorldViewModel.h"

WorldViewModel::WorldViewModel(Player *player) : player_(player) {}

void WorldViewModel::updateMaterials(Material (*materials)[28][2], const Vec2d& lastLeftUpPosition) const{
    auto world = getWorld();

    Vec2d leftUpPosition = getLeftUpPosition();

    if(true || leftUpPosition!=lastLeftUpPosition) {
        Material buffer[MAX_COLUMN][MAX_ROW][2];
        for(int i = 0; i < MAX_COLUMN; i++) {
            for (int j = 0; j < MAX_ROW; j++) {
                for (int k = 0; k <= 1; k++) {
                    auto block = world->getBlock(leftUpPosition.getBlockX() + i,
                                                  leftUpPosition.getBlockY() - j - 1, k);
                    if (block == nullptr)
                        buffer[i][j][k] = Material::BED_ROCK;
                    else
                        buffer[i][j][k] = block->getMaterial();
                }
            }
        }
        memcpy(materials, buffer, sizeof(int) * MAX_COLUMN * MAX_ROW * 2);
    }
}

Vec2d WorldViewModel::getCameraPosition() const {
    return player_->getLocation().toVec2d();
}

Vec2d WorldViewModel::getLeftUpPosition() const {
    Vec2d cameraPosition = getCameraPosition();
    Vec2d leftUpPosition(cameraPosition.getBlockX(),cameraPosition.getBlockY());
    leftUpPosition.add((int)std::floor(-MAX_COLUMN/2),(int)std::floor(MAX_ROW*0.618));
    return leftUpPosition;
}

long long WorldViewModel::getTicks() const {
    return getWorld()->getTicks();
}

World *WorldViewModel::getWorld() const {
    return player_->getWorld();
}
