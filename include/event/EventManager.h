//
// Created by Noy on 2023/7/6.
//

#ifndef FLATCRAFT_EVENTMANAGER_H
#define FLATCRAFT_EVENTMANAGER_H

#include "common.h"
#include "Event.h"

enum class EventPriority{
    LOWEST,
    LOW,
    NORMAL,
    HIGH,
    HIGHEST,
    MONITOR,
};

enum class EventType{

};

class EventManager {
public:
    void callEvent(Event& event);
    void registerListener(EventType type, EventPriority priority, std::function<void(Event*)> listener);
private:
    class Listeners{
    public:
        void execute(Event& event);
    private:
        std::unordered_multimap<EventPriority,std::function<void(Event*)>> byPriority_;
    };
    std::unordered_map<EventType,Listeners> byType_;
};


#endif //FLATCRAFT_EVENTMANAGER_H
