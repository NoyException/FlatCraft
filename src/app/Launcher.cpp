//
// Created by Noy on 2023/7/10.
//

#include "app/Launcher.h"
#include "window/graph.h"
#include "model/event/events.h"
#include "model/entity/entities.h"

void Launcher::init() {
    MaterialHelper::registerAllMaterials();
//    CommandType::init();
    game_ = FlatCraft::getInstance();
    FlatCraft::init();
    window_ = new Window();
}

void Launcher::start() {
    std::string saveName = "testSave4";
    if(game_->existsSave(saveName)){
        game_->loadSave(saveName);
    }
    else game_->createSave(saveName);
    //game_->loadSave()
    playerViewModel_ = new PlayerViewModel(game_->getPlayer());
    Binder::bindPlayer(window_->getPlayerView(), *playerViewModel_);

    worldViewModel_ = new WorldViewModel(game_->getPlayer());
    Binder::bindWorld(window_->getWorldView(), *worldViewModel_);

    EventManager::registerListener<ModelCreatedNotification<DroppedItem>>(EventPriority::MONITOR,[&](auto event){
        auto item = event->getModel();
        auto viewModel = new DroppedItemViewModel(item);
        auto view = window_->createDroppedItemView();
        Binder::bindDroppedItem(*view,*viewModel);
        droppedItemViewModels_.push_back(viewModel);
    });
    EventManager::registerListener<ModelDestroyedNotification<DroppedItem>>(EventPriority::MONITOR,[&](auto event){
        DroppedItemViewModel* vm = nullptr;
        for (auto &item: droppedItemViewModels_){
            if(item->getDroppedItem()==event->getModel())
                vm = item;
        }
        if(vm!=nullptr){
            droppedItemViewModels_.remove(vm);
            delete vm;
        }
    });
    std::cout << "Game starting" << std::endl;
    game_->start();
    std::cout << "Game started" << std::endl;

    viewThread_ = new std::thread([&](){
        window_->start();
    });

    consoleThread_ = new std::thread([&](){
        console_.run();
    });

    while(!graphFinish){
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    graphFinish = true;
}

void Launcher::stop() {
    game_->save();
    viewThread_->join();
    game_->stop();
    console_.stop();
    if(consoleThread_->joinable())
        consoleThread_->join();
    delete worldViewModel_;
    delete playerViewModel_;
    delete viewThread_;
    delete consoleThread_;
    for (auto &item: droppedItemViewModels_){
        delete item;
    }
    std::cout << "Game stopped" << std::endl;
}

void Launcher::end() {
    delete window_;
    std::cout << "Game ended" << std::endl;
}

void Launcher::test() {
    FlatCraft::getInstance()->getScheduler()->runTask([](){
    });
}
