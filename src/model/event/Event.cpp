//
// Created by Noy on 2023/7/6.
//

#include "model/event/Event.h"
#include "model/event/Listener.h"

Event::Event(Event *parent) : parent_(parent) {

}

void Event::call(EventInstance *eventInstance) const{
    call(eventInstance, EventPriority::LOWEST);
    call(eventInstance, EventPriority::LOW);
    call(eventInstance, EventPriority::NORMAL);
    call(eventInstance, EventPriority::HIGH);
    call(eventInstance, EventPriority::HIGHEST);
    call(eventInstance, EventPriority::MONITOR);
}

void Event::call(EventInstance *eventInstance, EventPriority priority) const {
    if(parent_ != nullptr) parent_->call(eventInstance, priority);
    for (const auto &listener: listeners_[static_cast<int>(priority)]){
        listener->listen(eventInstance);
    }
}
