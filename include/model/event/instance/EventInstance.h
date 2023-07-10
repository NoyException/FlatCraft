//
// Created by Noy on 2023/7/7.
//

#ifndef FLATCRAFT_EVENTINSTANCE_H
#define FLATCRAFT_EVENTINSTANCE_H

#include "model/event/Event.h"

/**
 * 事件实例，在发生每个事件时都会构造一个对应的实例
 */
class EventInstance{
public:
    virtual ~EventInstance() = default;
    [[nodiscard]] const Event* getEvent() const;
protected:
    explicit EventInstance(const Event* event);
private:
    const Event *event_;
};

#endif //FLATCRAFT_EVENTINSTANCE_H
