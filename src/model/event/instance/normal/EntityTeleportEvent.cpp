//
// Created by Noy on 2023/7/7.
//

#include "model/event/instance/normal/EntityTeleportEvent.h"
#include "model/event/EventType.h"
#include "model/entity/Entity.h"

EntityTeleportEvent::EntityTeleportEvent(Entity *entity, const Location &targetLocation) :
EntityEvent(EventType::ENTITY_TELEPORT_EVENT, entity), Cancelable(), target_(targetLocation) {}

Location EntityTeleportEvent::getCurrentLocation() const {
    return getEntity()->getLocation();
}

Location EntityTeleportEvent::getTargetLocation() const {
    return target_;
}

void EntityTeleportEvent::setTargetLocation(const Location &location) {
    target_ = location;
}
