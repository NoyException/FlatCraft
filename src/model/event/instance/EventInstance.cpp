//
// Created by Noy on 2023/7/7.
//

#include "model/event/instance/EventInstance.h"

EventInstance::EventInstance(const Event *event) : event_(event) {

}

const Event *EventInstance::getEvent() const {
    return event_;
}
