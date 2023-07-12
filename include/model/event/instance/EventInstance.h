//
// Created by Noy on 2023/7/7.
//

#ifndef FLATCRAFT_EVENTINSTANCE_H
#define FLATCRAFT_EVENTINSTANCE_H

#include "common.h"

class Event;

/**
 * 事件实例，在发生每个事件时都会构造一个对应的实例
 */
class EventInstance{
public:
    virtual ~EventInstance() = default;
    static Event* getEventType();
};

#endif //FLATCRAFT_EVENTINSTANCE_H
