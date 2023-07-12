//
// Created by Noy on 2023/7/6.
//

#ifndef FLATCRAFT_EVENTMANAGER_H
#define FLATCRAFT_EVENTMANAGER_H

#include "common.h"
#include "Event.h"
#include "EventType.h"
#include "Listener.h"

class EventManager {
public:
    template<class E>
    static void callEvent(E& event);

    template<class E>
    static Listener<E>* registerListener(EventPriority priority, std::function<void(E*)> listener);

    static void unregisterListener(BaseListener* listener);
private:
};

template<class E>
void EventManager::callEvent(E &event) {
    E::getEventType()->call(&event);
}

template<class E>
Listener<E> *EventManager::registerListener(EventPriority priority, std::function<void(E *)> listener) {
    Event *event = E::getEventType();
    auto l = std::make_unique<Listener<E>>(event,priority,listener);
    auto ptr = l.get();
    event->listeners_[static_cast<int>(priority)].push_back(std::move(l));
    return ptr;
}

#endif //FLATCRAFT_EVENTMANAGER_H
