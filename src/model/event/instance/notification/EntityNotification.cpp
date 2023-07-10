//
// Created by Noy on 2023/7/10.
//

#include "model/event/instance/notification/EntityNotification.h"
#include "model/event/EventType.h"

EntityNotification::EntityNotification(Entity *entity) : EventInstance(EventType::ENTITY_EVENT), entity_(entity) {}

EntityNotification::EntityNotification(const Event *event, Entity *entity) : EventInstance(event), entity_(entity) {}

Entity *EntityNotification::getEntity() {
    return entity_;
}

const Entity *EntityNotification::getEntity() const {
    return entity_;
}