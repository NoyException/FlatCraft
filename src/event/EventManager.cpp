//
// Created by Noy on 2023/7/7.
//

#include "event/EventManager.h"
#include "event/EventInstance.h"

void EventManager::callEvent(EventInstance &event) {
    event.getEvent()->call(&event);
}

void EventManager::registerListener(Event &event, EventPriority priority,
                                    const std::function<void(EventInstance *)>& listener) {
    event.listeners_[static_cast<int>(priority)].push_back(listener);
}