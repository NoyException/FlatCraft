//
// Created by Noy on 2023/7/7.
//

#ifndef FLATCRAFT_ENTITYTELEPORTEVENT_H
#define FLATCRAFT_ENTITYTELEPORTEVENT_H

#include "EntityEvent.h"
#include "event/Cancelable.h"

class EntityTeleportEvent : public EntityEvent, public Cancelable{
public:
    explicit EntityTeleportEvent(Entity* entity, const Location& targetLocation);
    [[nodiscard]] Location getCurrentLocation() const;
    [[nodiscard]] Location getTargetLocation() const;
    void setTargetLocation(const Location& location);
private:
    Location target_;
};


#endif //FLATCRAFT_ENTITYTELEPORTEVENT_H
