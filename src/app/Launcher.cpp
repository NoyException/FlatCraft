//
// Created by Noy on 2023/7/10.
//

#include "app/Launcher.h"
#include "model/event/events.h"
#include "view/graph.h"

void Launcher::init() {
    MaterialHelper::registerAllMaterials();
//    CommandType::init();
    game_ = FlatCraft::getInstance();
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
}

void Launcher::end() {
    delete window_;
}

void Launcher::test() {
    FlatCraft::getInstance()->getScheduler()->runTask([](){
        EventManager::registerListener(EventType::ENTITY_TELEPORT_EVENT,EventPriority::MONITOR,[](EventInstance* event){
            std::cout<<"TELEPORTING"<<std::endl;
        });
        EventManager::registerListener(EventType::ENTITY_EVENT,EventPriority::MONITOR,[](EventInstance* event){
            std::cout<<"ENTITY_EVENT"<<std::endl;
        });
    });
}
