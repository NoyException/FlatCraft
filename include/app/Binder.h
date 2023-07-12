//
// Created by Noy on 2023/7/10.
//

#ifndef FLATCRAFT_BINDER_H
#define FLATCRAFT_BINDER_H

#include "view/graph.h"
#include "viewmodel/WorldViewModel.h"
#include "viewmodel/PlayerViewModel.h"
#include "viewmodel/DroppedItemViewModel.h"

class Binder {
public:
    static void bindWorld(WorldView& view, WorldViewModel& viewModel);
    static void bindEntity(EntityView& view, EntityViewModel& viewModel);
    static void bindPlayer(PlayerView& view, PlayerViewModel& viewModel);
    static void bindDroppedItem(DroppedItemView& view, DroppedItemViewModel& viewModel);
};


#endif //FLATCRAFT_BINDER_H
