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
    MONITOR,
};

class EventInstance;

/**
 * 享元模式，代表了一个抽象事件类型
 */
class Event {
public:
    Event() = delete;
    explicit Event(Event* parent);
    /**
     * 子Event必须调用父Event的call
     * @param eventInstance 事件实例
     */
    void call(EventInstance* eventInstance) const;
    friend class EventManager;
private:
    Event *parent_;
    std::list<std::function<void(EventInstance*)>> listeners_[6];
};

#endif //FLATCRAFT_EVENT_H
