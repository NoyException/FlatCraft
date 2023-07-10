//
// Created by Noy on 2023/7/10.
//

#include "model/event/EventType.h"

Event* EventType::BASE_EVENT = nullptr;
Event* EventType::ENTITY_EVENT = nullptr;
Event* EventType::ENTITY_TELEPORT_EVENT = nullptr;
Event* EventType::WORLD_EVENT = nullptr;
Event* EventType::WORLD_LOADED_EVENT = nullptr;

void EventType::init() {
    BASE_EVENT = new Event(nullptr);
    ENTITY_EVENT = new Event(BASE_EVENT);
    ENTITY_TELEPORT_EVENT = new Event(ENTITY_EVENT);
    WORLD_EVENT = new Event(BASE_EVENT);
    WORLD_LOADED_EVENT = new Event(WORLD_EVENT);
}