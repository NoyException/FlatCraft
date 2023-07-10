//
// Created by Noy on 2023/7/7.
//

#ifndef FLATCRAFT_ENTITYEVENT_H
#define FLATCRAFT_ENTITYEVENT_H

#include "model/event/instance/EventInstance.h"

class Entity;

class EntityEvent : public EventInstance{
public:
    explicit EntityEvent(Entity* entity);
    Entity* getEntity();
    [[nodiscard]] const Entity* getEntity() const;
protected:
    EntityEvent(const Event* event, Entity* entity);
private:
    Entity* entity_;
};


#endif //FLATCRAFT_ENTITYEVENT_H
