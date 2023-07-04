//
// Created by Noy on 2023/7/4.
//

#ifndef FLATCRAFT_FLATCRAFT_H
#define FLATCRAFT_FLATCRAFT_H

#include "common.h"
#include "world/World.h"
#include "entity/player/Player.h"
#include "scheduler/Scheduler.h"

class FlatCraft {
public:
    FlatCraft();
    void start();
    void createWorld(const std::string& name);
    [[nodiscard]] World* getWorld(const std::string& name) const;
    Player* getPlayer();
    static FlatCraft* getInstance();
private:
    //name->World
    std::map<std::string,std::unique_ptr<World>> worlds_;
    Player player_;
    Scheduler scheduler_;
    static std::unique_ptr<FlatCraft> instance;
};

#endif //FLATCRAFT_FLATCRAFT_H
