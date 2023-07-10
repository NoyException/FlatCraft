//
// Created by Noy on 2023/7/10.
//

#include "app/Launcher.h"
#include "model/event/events.h"

void Launcher::init() {
    MaterialHelper::registerAllMaterials();
//    CommandType::init();
    game_ = FlatCraft::getInstance();
}

void Launcher::start() {
    game_->createSave("testSave3");
    //game_->loadSave()
    playerView_ = new PlayerView();
    playerViewModel_ = new PlayerViewModel(game_->getPlayer());
    Binder::bindPlayer(*playerView_, *playerViewModel_);

    worldView_ = new WorldView();
    worldViewModel_ = new WorldViewModel(game_->getPlayer());
    Binder::bindWorld(*worldView_, *worldViewModel_);
    std::cout << "Game starting" << std::endl;
    game_->start();
    std::cout << "Game started" << std::endl;

    viewThread_ = new std::thread([&](){
        worldView_->display();
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
    delete worldView_;
    delete playerViewModel_;
    delete playerView_;
}

void Launcher::end() {
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
