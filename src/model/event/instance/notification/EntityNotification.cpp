//
// Created by Noy on 2023/7/10.
//

#include "model/event/instance/notification/EntityNotification.h"
#include "model/event/EventType.h"

EntityNotification::EntityNotification(Entity *entity) : entity_(entity) {}

Entity *EntityNotification::getEntity() {
    return entity_;
}

const Entity *EntityNotification::getEntity() const {
    return entity_;
}

Event *EntityNotification::getEventType() {
    return EventType::NOTIFICATION_EVENT;
}
