//
// Created by Noy on 2023/7/10.
//

#include "model/event/instance/normal/WorldWeatherChangeEvent.h"
#include "model/event/EventType.h"
#include "model/world/World.h"

WorldWeatherChangeEvent::WorldWeatherChangeEvent(World *world, Weather newWeather) :
WorldEvent(world), Cancelable(), newWeather_(newWeather) {}

Weather WorldWeatherChangeEvent::getOldWeather() const {
    return getWorld()->getWeather();
}

Weather WorldWeatherChangeEvent::getNewWeather() const {
    return newWeather_;
}

void WorldWeatherChangeEvent::setNewWeather(Weather newWeather) {
    newWeather_ = newWeather;
}

Event *WorldWeatherChangeEvent::getEventType() {
    return EventType::WORLD_WEATHER_CHANGE_EVENT;
}
