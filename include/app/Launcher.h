//
// Created by Noy on 2023/7/10.
//

#ifndef FLATCRAFT_LAUNCHER_H
#define FLATCRAFT_LAUNCHER_H

#include "common.h"
#include "Binder.h"
#include "model/FlatCraft.h"
#include "viewmodel/PlayerViewModel.h"
#include "viewmodel/DroppedItemViewModel.h"
#include "window/graph.h"
#include "Console.h"

class Launcher {
public:
    Launcher() = default;
    void init();
    void start();
    void stop();
    void end();
private:
    void test();
    FlatCraft* game_ = nullptr;
    Window* window_ = nullptr;
    PlayerViewModel* playerViewModel_ = nullptr;
    WorldViewModel* worldViewModel_ = nullptr;
    Console console_;
    std::thread* viewThread_ = nullptr;
    std::thread* consoleThread_ = nullptr;
    std::list<DroppedItemViewModel*> droppedItemViewModels_;
};


#endif //FLATCRAFT_LAUNCHER_H
