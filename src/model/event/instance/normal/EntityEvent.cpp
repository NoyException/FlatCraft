//
// Created by Noy on 2023/7/7.
//

#include "model/event/EventType.h"
#include "model/event/instance/normal/EntityEvent.h"
#include "model/entity/Entity.h"

EntityEvent::EntityEvent(Entity *entity) : EventInstance(EventType::ENTITY_EVENT), entity_(entity) {}

EntityEvent::EntityEvent(const Event *event, Entity *entity) : EventInstance(event), entity_(entity) {}

Entity *EntityEvent::getEntity() {
    return entity_;
}

const Entity *EntityEvent::getEntity() const {
    return entity_;
}
