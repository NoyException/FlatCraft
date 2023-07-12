//
// Created by Noy on 2023/7/4.
//

#ifndef FLATCRAFT_FLATCRAFT_H
#define FLATCRAFT_FLATCRAFT_H

#include "common.h"
#include "model/world/World.h"
#include "model/entity/player/Player.h"
#include "model/scheduler/Scheduler.h"
#include "model/event/EventManager.h"

class FlatCraft {
public:
    friend class Entity;
    static void init();
    void start();
    void stop();
    void createWorld(const std::string& name);
    void loadSave(const std::string& name);
    void save();
    [[nodiscard]] bool existsSave(const std::string &name) const;
    void createSave(const std::string &name);
    [[nodiscard]] World* getWorld(const std::string& name) const;
    Player* getPlayer();
    Entity* getEntity(int id);
    Scheduler* getScheduler();
    EventManager* getEventManager();
    template<class T, typename... Args>
    T* createEntity(Args&&... args);
    static FlatCraft* getInstance();
    friend std::unique_ptr<FlatCraft> std::make_unique<FlatCraft>();
private:
    FlatCraft();
    void destroyEntity(Entity* entity);

    void createPlayer();
    void loadPlayer();
    void savePlayer();

    void loadEntities();
    void saveEntities();

    void loadWorld(const std::string& name);
    void loadWorlds();
    void saveWorld(const std::string& name);
    void saveWorlds();
    //name->World
    std::map<std::string,std::unique_ptr<World>> worlds_;
    std::unique_ptr<Player> player_;
    std::unordered_map<int,std::unique_ptr<Entity>> entities_;
    Scheduler scheduler_;
    int nextEntityId_;
    long long ticks_;
    EventManager eventManager_;
    std::string save_;
    static std::unique_ptr<FlatCraft> instance;
};

template<class T, typename... Args>
T* FlatCraft::createEntity(Args&&... args) {
    static_assert(std::is_base_of<Entity, T>::value, "T must be a subclass of Entity");
    std::unique_ptr<T> ptr = std::make_unique<T>(std::forward<Args>(args)...);
    T* t = ptr.get();
    t->id_ = nextEntityId_;
    entities_.emplace(nextEntityId_,std::move(ptr));
    nextEntityId_++;
    return t;
}

#endif //FLATCRAFT_FLATCRAFT_H
