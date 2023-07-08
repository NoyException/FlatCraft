//
// Created by Noy on 2023/7/3.
//

#ifndef FLATCRAFT_ENTITY_H
#define FLATCRAFT_ENTITY_H

#include "common.h"
#include "Location.h"
#include "scheduler/Task.h"

class Entity {
public:
    explicit Entity(const Location& spawnLocation);
    virtual ~Entity();
    [[nodiscard]] virtual nlohmann::json serialize() const;
    [[nodiscard]] Location getLocation() const;
    [[nodiscard]] World* getWorld() const;
    void teleport(const Location& location);
    void move();
    void move(const Vec2d& dv);
    [[nodiscard]] bool isOnGround() const;
    [[nodiscard]] Vec2d getVelocity() const;
    [[nodiscard]] BoundingBox getBoundingBox() const;
protected:
    Location location_;
    Vec2d velocity_;
    BoundingBox boundingBox_;
private:
    Task* physicsTask_;
};


#endif //FLATCRAFT_ENTITY_H
