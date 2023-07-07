//
// Created by Noy on 2023/7/7.
//

#include "event/EventManager.h"
#include "event/instance/EntityEvent.h"

EntityEvent::EntityEvent(Entity *entity) : EventInstance(EventManager::ENTITY_EVENT), entity_(entity) {

}

EntityEvent::EntityEvent(const Event *event, Entity *entity) : EventInstance(event), entity_(entity) {

}

Entity *EntityEvent::getEntity() {
    return entity_;
}

const Entity *EntityEvent::getEntity() const {
    return entity_;
}
