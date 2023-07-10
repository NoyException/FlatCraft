//
// Created by Noy on 2023/7/10.
//

#include "app/Launcher.h"
#include "model/event/instance/WorldLoadedEvent.h"

void Launcher::init() {
    MaterialHelper::registerAllMaterials();
    game_ = FlatCraft::getInstance();
    graph_ = new Graph();
}

void Launcher::start() {
    game_->createSave("testSave3");
    std::cout << "Game starting" << std::endl;
    game_->start();
    std::cout << "Game started" << std::endl;
    worldViewModel_ = new WorldViewModel(game_->getPlayer());
    Binder::bindWorld(*graph_, *worldViewModel_);

    viewThread_ = new std::thread([&](){
        graph_->display();
    });

    while(!graphFinish){
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

void Launcher::stop() {
    game_->save();
    std::cout << "Game ended" << std::endl;
    game_->stop();
}

void Launcher::end() {
    viewThread_->join();
    delete graph_;
    delete worldViewModel_;
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

    std::this_thread::sleep_for(std::chrono::seconds(3));
    FlatCraft::getInstance()->getScheduler()->runTask([](){
        auto player = FlatCraft::getInstance()->getPlayer();
        player->setFlying(true);
//        player->teleport(Location(*player->getWorld(),3.6,64));
//        player->setVelocity(Vec2d(0,-0.28));
//        player->teleport(Location(*player->getWorld(),-66.58,64.9));
//        player->setVelocity(Vec2d(0,-0.2));
    });
}
