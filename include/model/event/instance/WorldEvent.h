//
// Created by Noy on 2023/7/7.
//

#ifndef FLATCRAFT_ENTITYEVENT_H
#define FLATCRAFT_ENTITYEVENT_H

#include "EventInstance.h"
#include "model/world/World.h"

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


#endif //FLATCRAFT_ENTITYEVENT_H
