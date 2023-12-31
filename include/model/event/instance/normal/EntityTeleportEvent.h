//
// Created by Noy on 2023/7/7.
//

#ifndef FLATCRAFT_ENTITYTELEPORTEVENT_H
#define FLATCRAFT_ENTITYTELEPORTEVENT_H

#include "EntityEvent.h"
#include "model/event/Cancelable.h"
#include "model/Location.h"

class EntityTeleportEvent : public EntityEvent, public Cancelable{
public:
    EntityTeleportEvent(Entity* entity, const Location& targetLocation);
    [[nodiscard]] Location getCurrentLocation() const;
    [[nodiscard]] Location getTargetLocation() const;
    void setTargetLocation(const Location& location);
    static Event* getEventType();
private:
    Location target_;
};


#endif //FLATCRAFT_ENTITYTELEPORTEVENT_H
