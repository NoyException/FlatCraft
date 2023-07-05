//
// Created by Noy on 2023/7/4.
//

#include "FlatCraft.h"
#include <windows.h>
#include <filesystem>

FlatCraft::FlatCraft() : player_(Location("what",0,64)) {
}

void FlatCraft::start() {
    createWorld("test");
//    save_="test";
//    loadPlayer();
//    savePlayer();
//    loadPlayer();
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
    std::ifstream in(save_+"/player.dat");
    if(in.is_open()){
        std::string s((std::istreambuf_iterator<char> (in)), (std::istreambuf_iterator<char> ()));
        in.close();
        if(!s.empty()){
            player_ = Player::deserialize(nlohmann::json::parse(s));
            std::cout<<"loaded"<<std::endl<<player_.getLocation().serialize().dump();
            return;
        }
    }
    player_ = Player{Location{"main_world",0,64}};
}

void FlatCraft::loadWorld(const std::string &name) {

}

void FlatCraft::save() {
    std::filesystem::create_directories(save_);
    savePlayer();
    saveWorlds();
}

void FlatCraft::savePlayer() {
    std::ofstream out(save_+"/player.dat");
    if(out.is_open()){
        out<<player_.serialize().dump();
        out.close();
    }
}

void FlatCraft::saveWorld(const std::string &name) {

}

void FlatCraft::saveWorlds() {

}
