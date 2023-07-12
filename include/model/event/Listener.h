//
// Created by Noy on 2023/7/12.
//

#ifndef FLATCRAFT_LISTENER_H
#define FLATCRAFT_LISTENER_H

#include "instance/EventInstance.h"
#include "Event.h"

class BaseListener{
public:
    BaseListener(Event *event, EventPriority priority);
    virtual ~BaseListener() = default;
    virtual void listen(EventInstance* event) const = 0;
    [[nodiscard]] Event *getEvent() const;
    [[nodiscard]] EventPriority getPriority() const;
private:
    Event* event_;
    EventPriority priority_;
};

template<class E>
class Listener : public BaseListener {
public:
    Listener(Event *event, EventPriority priority, const std::function<void(E *)> &lambda);
    void listen(EventInstance* event) const override;
private:
    std::function<void(E*)> fun_;
};

template<class E>
Listener<E>::Listener(Event *event, EventPriority priority, const std::function<void(E *)> &lambda) :
BaseListener(event,priority), fun_(lambda) {}

template<class E>
void Listener<E>::listen(EventInstance *event) const {
    auto e = dynamic_cast<E*>(event);
    if(e != nullptr) fun_(e);
}

#endif //FLATCRAFT_LISTENER_H
