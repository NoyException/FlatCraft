//
// Created by Noy on 2023/7/4.
//

#include "FlatCraft.h"
#include <windows.h>

FlatCraft::FlatCraft() : player_(Location("what",0,64)) {
}

void FlatCraft::start() {
    createWorld("test");
}

void FlatCraft::createWorld(const std::string &name) {
    worlds_.emplace(name, std::make_unique<World>(name));
}

FlatCraft *FlatCraft::getInstance() {
    return instance.get();
}

std::unique_ptr<FlatCraft> FlatCraft::instance = std::make_unique<FlatCraft>();

World *FlatCraft::getWorld(const std::string &name) const {
    return worlds_.find(name)->second.get();
}

Player *FlatCraft::getPlayer() {
    return &player_;
}

void FlatCraft::loadSave(const std::string &name) {

    save_ = name;
    loadPlayer();
    loadWorld(player_.getLocation().getRawWorld());

    static int cnt[4];
    scheduler_.runTaskTimer([](){
        if (GetAsyncKeyState('W') & 0x8000) {
            cnt[0]++;//std::cout << "W is pressed\n";
        }

        // Check the state of A key
        if (GetAsyncKeyState('A') & 0x8000) {
            cnt[1]++;//std::cout << "A is pressed\n";
        }

        // Check the state of S key
        if (GetAsyncKeyState('S') & 0x8000) {
            cnt[2]++;//std::cout << "S is pressed\n";
        }

        // Check the state of D key
        if (GetAsyncKeyState('D') & 0x8000) {
            cnt[3]++;//std::cout << "D is pressed\n";
        }
    },0,0);
    scheduler_.runTaskLater([](){
        std::cout << "A:" << cnt[0] << std::endl;
        std::cout << "B:" << cnt[1] << std::endl;
        std::cout << "C:" << cnt[2] << std::endl;
        std::cout << "D:" << cnt[3] << std::endl;
    },200);
    scheduler_.start();
}

void FlatCraft::loadPlayer() {

}

void FlatCraft::loadWorld(const std::string &name) {

}

void FlatCraft::save() {
    savePlayer();
    saveWorlds();
}

void FlatCraft::savePlayer() {

}

void FlatCraft::saveWorld(const std::string &name) {

}

void FlatCraft::saveWorlds() {

}
