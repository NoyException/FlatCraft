//
// Created by Noy on 2023/7/10.
//

#ifndef FLATCRAFT_WORLDWEATHERCHANGEEVENT_H
#define FLATCRAFT_WORLDWEATHERCHANGEEVENT_H

#include "WorldEvent.h"
#include "../../Cancelable.h"

class WorldWeatherChangeEvent : public WorldEvent, public Cancelable{
public:
    WorldWeatherChangeEvent(World* world, Weather newWeather);

    [[nodiscard]] Weather getOldWeather() const;

    [[nodiscard]] Weather getNewWeather() const;

    void setNewWeather(Weather newWeather);

    static Event* getEventType();
private:
    Weather newWeather_;
};


#endif //FLATCRAFT_WORLDWEATHERCHANGEEVENT_H
