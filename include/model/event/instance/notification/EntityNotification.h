//
// Created by Noy on 2023/7/10.
//

#ifndef FLATCRAFT_ENTITYNOTIFICATION_H
#define FLATCRAFT_ENTITYNOTIFICATION_H

#include "../EventInstance.h"

class Entity;

class EntityNotification : public EventInstance {
public:
    EntityNotification(const Event* event, Entity* entity);
    explicit EntityNotification(Entity* entity);
    Entity* getEntity();
    [[nodiscard]] const Entity* getEntity() const;
private:
    Entity* entity_;
};


#endif //FLATCRAFT_ENTITYNOTIFICATION_H
