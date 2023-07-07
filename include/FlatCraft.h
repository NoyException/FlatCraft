//
// Created by Noy on 2023/7/4.
//

#ifndef FLATCRAFT_FLATCRAFT_H
#define FLATCRAFT_FLATCRAFT_H

#include "common.h"
#include "world/World.h"
#include "entity/player/Player.h"
#include "scheduler/Scheduler.h"
#include "event/EventManager.h"

class FlatCraft {
public:
    void start();
    void stop();
    void createWorld(const std::string& name);
    void loadSave(const std::string& name);
    void save();
    [[nodiscard]] bool existsSave(const std::string &name) const;
    void createSave(const std::string &name);
    [[nodiscard]] World* getWorld(const std::string& name) const;
    Player* getPlayer();
    Scheduler* getScheduler();
    EventManager* getEventManager();
    static FlatCraft* getInstance();
    friend std::unique_ptr<FlatCraft> std::make_unique<FlatCraft>(void);
private:
    FlatCraft();
    void loadPlayer();
    void savePlayer();

    void loadWorld(const std::string& name);
    void loadWorlds();
    void saveWorld(const std::string& name);
    void saveWorlds();
    //name->World
    std::map<std::string,std::unique_ptr<World>> worlds_;
    std::unique_ptr<Player> player_;
    Scheduler scheduler_;
    long long ticks_;
    EventManager eventManager_;
    std::string save_;
    static std::unique_ptr<FlatCraft> instance;
};

#endif //FLATCRAFT_FLATCRAFT_H
