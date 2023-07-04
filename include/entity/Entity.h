//
// Created by Noy on 2023/7/3.
//

#ifndef FLATCRAFT_ENTITY_H
#define FLATCRAFT_ENTITY_H

#include "common.h"
#include "Location.h"

class Entity {
public:
    explicit Entity(const Location& spawnLocation);
    [[nodiscard]] Location getLocation() const;
    void teleport(const Location& location);
private:
    Location location_;
};


#endif //FLATCRAFT_ENTITY_H
