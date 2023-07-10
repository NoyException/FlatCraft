//
// Created by Noy on 2023/7/10.
//

#ifndef FLATCRAFT_BINDER_H
#define FLATCRAFT_BINDER_H

#include "view/graph.h"
#include "viewmodel/WorldViewModel.h"

class Binder {
public:
    static void bindWorld(Graph& graph, WorldViewModel& viewModel);
};


#endif //FLATCRAFT_BINDER_H
