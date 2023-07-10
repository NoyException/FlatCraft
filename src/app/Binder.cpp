//
// Created by Noy on 2023/7/10.
//

#include "app/Binder.h"

void Binder::bindWorld(Graph &graph, WorldViewModel &viewModel) {
    graph.updateMaterials_ = [&](Material material[][28][2], const Vec2d& lastLeftUpPosition){
        viewModel.updateMaterials(material, lastLeftUpPosition);
    };
    graph.getLeftUpPosition_ = [&](){
        return viewModel.getLeftUpPosition();
    };
    graph.getCameraPosition_ = [&](){
        return viewModel.getCameraPosition();
    };
    graph.getTicks_ = [&](){
        return viewModel.getTicks();
    };
}
