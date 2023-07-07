//
// Created by Noy on 2023/7/7.
//

#include "event/EventManager.h"
#include "event/instance/EventInstance.h"

EventManager::EventManager(){
    BASE_EVENT = new Event(nullptr);
    ENTITY_EVENT = new Event(BASE_EVENT);
    ENTITY_TELEPORT_EVENT = new Event(ENTITY_EVENT);
}

EventManager::~EventManager(){
    delete BASE_EVENT;
    delete ENTITY_EVENT;
    delete ENTITY_TELEPORT_EVENT;
}

void EventManager::callEvent(EventInstance &event) {
    event.getEvent()->call(&event);
}

void EventManager::registerListener(Event *event, EventPriority priority,
                                    const std::function<void(EventInstance *)>& listener) {
    event->listeners_[static_cast<int>(priority)].push_back(listener);
}

Event* EventManager::BASE_EVENT = nullptr;
Event* EventManager::ENTITY_EVENT = nullptr;
Event* EventManager::ENTITY_TELEPORT_EVENT = nullptr;