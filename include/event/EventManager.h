//
// Created by Noy on 2023/7/6.
//

#ifndef FLATCRAFT_EVENTMANAGER_H
#define FLATCRAFT_EVENTMANAGER_H

#include "common.h"
#include "Event.h"

class EventManager {
public:
    Event BASE_EVENT;
    static void callEvent(EventInstance& event) ;
    static void registerListener(Event& event, EventPriority priority, const std::function<void(EventInstance*)>& listener) ;
private:
};


#endif //FLATCRAFT_EVENTMANAGER_H
