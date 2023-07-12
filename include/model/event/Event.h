//
// Created by Noy on 2023/7/6.
//

#ifndef FLATCRAFT_EVENT_H
#define FLATCRAFT_EVENT_H

#include "common.h"

enum class EventPriority : int{
    LOWEST,
    LOW,
    NORMAL,
    HIGH,
    HIGHEST,
    /**该级别下要求不可以改变事件结果，仅做监听*/
    MONITOR,
};

class EventInstance;
class BaseListener;

/**
 * 享元模式，代表了一个抽象事件类型
 */
class Event {
public:
    Event() = delete;
    explicit Event(Event* parent);
    void call(EventInstance* eventInstance) const;
    friend class EventManager;
private:
    void call(EventInstance* eventInstance, EventPriority priority) const;
    Event *parent_;
    std::list<std::unique_ptr<BaseListener>> listeners_[6];
};

#endif //FLATCRAFT_EVENT_H
