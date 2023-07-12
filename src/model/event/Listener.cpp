//
// Created by Noy on 2023/7/12.
//

#include "model/event/Listener.h"

BaseListener::BaseListener(Event *event, EventPriority priority) : event_(event), priority_(priority) {}

Event *BaseListener::getEvent() const {
    return event_;
}

EventPriority BaseListener::getPriority() const {
    return priority_;
}
