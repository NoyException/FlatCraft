//
// Created by Noy on 2023/7/10.
//

#include "model/event/instance/normal/WorldEvent.h"
#include "model/event/EventType.h"

WorldEvent::WorldEvent(World *world) : EventInstance(EventType::WORLD_EVENT), world_(world) {}

WorldEvent::WorldEvent(const Event *event, World *world) : EventInstance(event), world_(world) {}

World *WorldEvent::getWorld() {
    return world_;
}

const World *WorldEvent::getWorld() const {
    return world_;
}
