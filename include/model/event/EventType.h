//
// Created by Noy on 2023/7/10.
//

#ifndef FLATCRAFT_EVENTTYPE_H
#define FLATCRAFT_EVENTTYPE_H

#include "Event.h"

class EventType{
public:
    static void init();
    static Event* BASE_EVENT;
    static Event* ENTITY_EVENT;
    static Event* ENTITY_TELEPORT_EVENT;
    static Event* WORLD_EVENT;
    static Event* WORLD_LOADED_EVENT;
};


#endif //FLATCRAFT_EVENTTYPE_H
