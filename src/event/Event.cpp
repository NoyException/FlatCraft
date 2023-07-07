//
// Created by Noy on 2023/7/6.
//

#include "event/Event.h"

void Event::call(EventInstance *eventInstance) const{
    for (auto &listenerList : listeners_) {
        for (const auto &listener: listenerList){
            listener(eventInstance);
        }
    }
}
