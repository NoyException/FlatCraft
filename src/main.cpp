#include "common.h"
#include "FlatCraft.h"
#include <thread>
#include "graphics/graph.h"

#undef main
int main(){
//    SDL_main(0,{});
    FlatCraft* game = FlatCraft::getInstance();
    game->createSave("testSave2");
    std::cout << "Game starting" << std::endl;
    game->start();
    std::cout << "Game started" << std::endl;
    FlatCraft::getInstance()->getScheduler()->runTask([](){
        EventManager::registerListener(EventManager::ENTITY_TELEPORT_EVENT,EventPriority::MONITOR,[](EventInstance* event){
            std::cout<<"TELEPORTING"<<std::endl;
        });
        EventManager::registerListener(EventManager::ENTITY_EVENT,EventPriority::MONITOR,[](EventInstance* event){
            std::cout<<"ENTITY_EVENT"<<std::endl;
        });
    });

    std::this_thread::sleep_for(std::chrono::seconds(1));
//    FlatCraft::getInstance()->getScheduler()->runTask([](){
//        auto player = FlatCraft::getInstance()->getPlayer();
//        auto location = player->getLocation();
//        location.add(0,10);
//        player->teleport(location);
//    });
    std::thread graphThread(graphMain, game);

    std::this_thread::sleep_for(std::chrono::seconds(100));
    game->save();
    std::cout << "Game ended" << std::endl;
    game->stop();
}