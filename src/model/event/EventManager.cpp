//
// Created by Noy on 2023/7/7.
//

#include "model/event/EventManager.h"
#include "model/event/instance/EventInstance.h"

void EventManager::callEvent(EventInstance &event) {
    event.getEvent()->call(&event);
}

void EventManager::registerListener(Event *event, EventPriority priority,
                                    const std::function<void(EventInstance *)>& listener) {
    event->listeners_[static_cast<int>(priority)].push_back(listener);
}
