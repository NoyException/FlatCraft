//
// Created by Noy on 2023/7/6.
//

#include "event/Event.h"

Event::Event(Event *parent) : parent_(parent) {

}

void Event::call(EventInstance *eventInstance) const{
    if(parent_ != nullptr) parent_->call(eventInstance);
    for (auto &listenerList : listeners_) {
        for (const auto &listener: listenerList){
            listener(eventInstance);
        }
    }
}
