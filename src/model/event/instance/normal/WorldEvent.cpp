//
// Created by Noy on 2023/7/10.
//

#include "model/event/instance/normal/WorldEvent.h"
#include "model/event/EventType.h"

WorldEvent::WorldEvent(World *world) : world_(world) {}

World *WorldEvent::getWorld() {
    return world_;
}

const World *WorldEvent::getWorld() const {
    return world_;
}

Event *WorldEvent::getEventType() {
    return EventType::WORLD_EVENT;
}
