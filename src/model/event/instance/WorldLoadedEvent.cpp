//
// Created by Noy on 2023/7/10.
//

#include "model/event/instance/WorldLoadedEvent.h"
#include "model/event/EventType.h"

WorldLoadedEvent::WorldLoadedEvent(World *world) : WorldEvent(EventType::WORLD_LOADED_EVENT, world) {}
