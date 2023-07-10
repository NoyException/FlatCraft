//
// Created by Noy on 2023/7/10.
//

#include "model/event/instance/normal/WorldLoadedEvent.h"
#include "model/event/EventType.h"
#include "model/world/World.h"

WorldLoadedEvent::WorldLoadedEvent(World *world) : WorldEvent(EventType::WORLD_LOADED_EVENT, world) {}
