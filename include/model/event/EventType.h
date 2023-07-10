//
// Created by Noy on 2023/7/10.
//

#ifndef FLATCRAFT_EVENTTYPE_H
#define FLATCRAFT_EVENTTYPE_H

#include "Event.h"

class EventType{
public:
    static void init();
    static Event* NORMAL_EVENT;
    static Event* ENTITY_EVENT;
    static Event* ENTITY_TELEPORT_EVENT;
    static Event* WORLD_EVENT;
    static Event* WORLD_LOADED_EVENT;
    static Event* WORLD_WEATHER_CHANGE_EVENT;

    static Event* NOTIFICATION_EVENT;
    static Event* VALUE_CHANGED_NOTIFICATION;
    static Event* ENTITY_NOTIFICATION;
    static Event* ENTITY_LOCATION_CHANGED_NOTIFICATION;
    static Event* ENTITY_DIRECTION_CHANGED_NOTIFICATION;
    static Event* ENTITY_VELOCITY_CHANGED_NOTIFICATION;
};


#endif //FLATCRAFT_EVENTTYPE_H
