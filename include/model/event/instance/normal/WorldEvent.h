//
// Created by Noy on 2023/7/7.
//

#ifndef FLATCRAFT_WORLDEVENT_H
#define FLATCRAFT_WORLDEVENT_H

#include "../EventInstance.h"

class World;

class WorldEvent : public EventInstance{
public:
    explicit WorldEvent(World* world);
    World* getWorld();
    [[nodiscard]] const World* getWorld() const;
protected:
    WorldEvent(const Event* event, World* world);
private:
    World* world_;
};


#endif //FLATCRAFT_WORLDEVENT_H
