//
// Created by Noy on 2023/7/7.
//

#ifndef FLATCRAFT_EVENTINSTANCE_H
#define FLATCRAFT_EVENTINSTANCE_H

#include "Event.h"

/**
 * 事件实例，在发生每个事件时都会构造一个对应的实例
 */
class EventInstance{
public:
    explicit EventInstance(const Event& event);
    virtual ~EventInstance() = default;
    [[nodiscard]] const Event* getEvent() const;
private:
    const Event *event_;
};

#endif //FLATCRAFT_EVENTINSTANCE_H
