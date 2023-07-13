//
// Created by Noy on 2023/7/10.
//

#include "app/Launcher.h"
#include "view/graph.h"
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

    while(!graphFinish){
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

void Launcher::stop() {
    game_->save();
    viewThread_->join();
    std::cout << "Game ended" << std::endl;
    game_->stop();
    delete worldViewModel_;
    delete playerViewModel_;
    for (auto &item: droppedItemViewModels_){
        delete item;
    }
}

void Launcher::end() {
    delete window_;
}

void Launcher::test() {
    FlatCraft::getInstance()->getScheduler()->runTask([](){
    });
}
