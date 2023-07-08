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

    std::thread graphThread(graphMain);

//    std::this_thread::sleep_for(std::chrono::seconds(3));
//    FlatCraft::getInstance()->getScheduler()->runTask([](){
//        auto player = FlatCraft::getInstance()->getPlayer();
//        player->teleport(Location(*player->getWorld(),-66.58,65.08));
//        player->setVelocity(Vec2d(0,-0.28));
////        player->teleport(Location(*player->getWorld(),-66.58,64.9));
////        player->setVelocity(Vec2d(0,-0.2));
//    });

    while(!graphFinish){
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    game->save();
    std::cout << "Game ended" << std::endl;
    game->stop();
}