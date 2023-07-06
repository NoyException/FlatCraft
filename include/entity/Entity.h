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
    [[nodiscard]] World* getWorld() const;
    void teleport(const Location& location);
    [[nodiscard]] virtual nlohmann::json serialize() const;
protected:
    Location location_;
private:
};


#endif //FLATCRAFT_ENTITY_H
