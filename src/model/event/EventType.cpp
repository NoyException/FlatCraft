//
// Created by Noy on 2023/7/10.
//

#include "model/event/EventType.h"

Event* EventType::NORMAL_EVENT = nullptr;
Event* EventType::ENTITY_EVENT = nullptr;
Event* EventType::ENTITY_TELEPORT_EVENT = nullptr;
Event* EventType::WORLD_EVENT = nullptr;
Event* EventType::WORLD_LOADED_EVENT = nullptr;
Event* EventType::WORLD_WEATHER_CHANGE_EVENT = nullptr;

Event* EventType::NOTIFICATION_EVENT = nullptr;
Event* EventType::VALUE_CHANGED_NOTIFICATION = nullptr;
Event* EventType::MODEL_CREATED_NOTIFICATION = nullptr;
Event* EventType::MODEL_DESTROYED_NOTIFICATION = nullptr;

void EventType::init() {
    NORMAL_EVENT = new Event(nullptr);
    ENTITY_EVENT = new Event(NORMAL_EVENT);
    ENTITY_TELEPORT_EVENT = new Event(ENTITY_EVENT);
    WORLD_EVENT = new Event(NORMAL_EVENT);
    WORLD_LOADED_EVENT = new Event(WORLD_EVENT);
    WORLD_WEATHER_CHANGE_EVENT = new Event(WORLD_EVENT);

    NOTIFICATION_EVENT = new Event(nullptr);
    VALUE_CHANGED_NOTIFICATION = new Event(NOTIFICATION_EVENT);
    MODEL_CREATED_NOTIFICATION = new Event(NOTIFICATION_EVENT);
    MODEL_DESTROYED_NOTIFICATION = new Event(NOTIFICATION_EVENT);
}