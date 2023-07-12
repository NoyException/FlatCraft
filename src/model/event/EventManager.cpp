//
// Created by Noy on 2023/7/7.
//

#include "model/event/EventManager.h"

void EventManager::unregisterListener(BaseListener *listener) {
    listener->getEvent()->listeners_[static_cast<int>(listener->getPriority())].remove_if([&](auto& ptr){
        return listener==ptr.get();
    });
}
