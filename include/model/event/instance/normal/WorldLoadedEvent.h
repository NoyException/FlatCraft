//
// Created by Noy on 2023/7/10.
//

#ifndef FLATCRAFT_WORLDLOADEDEVENT_H
#define FLATCRAFT_WORLDLOADEDEVENT_H

#include "WorldEvent.h"

class WorldLoadedEvent : public WorldEvent{
public:
    explicit WorldLoadedEvent(World* world);
    static Event* getEventType();
};


#endif //FLATCRAFT_WORLDLOADEDEVENT_H
