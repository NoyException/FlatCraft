//
// Created by Noy on 2023/7/7.
//

#include "event/instance/EntityTeleportEvent.h"
#include "event/EventManager.h"

EntityTeleportEvent::EntityTeleportEvent(Entity *entity, const Location &targetLocation) :
EntityEvent(EventManager::ENTITY_TELEPORT_EVENT, entity), Cancelable(), target_(targetLocation) {

}

Location EntityTeleportEvent::getCurrentLocation() const {
    return getEntity()->getLocation();
}

Location EntityTeleportEvent::getTargetLocation() const {
    return target_;
}

void EntityTeleportEvent::setTargetLocation(const Location &location) {
    target_ = location;
}
