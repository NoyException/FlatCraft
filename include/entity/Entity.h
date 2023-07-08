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
    void move(const Vec2d& v);
    [[nodiscard]] bool hasFriction() const;
    [[nodiscard]] bool hasGravity() const;
    [[nodiscard]] bool isOnGround() const;
    [[nodiscard]] Vec2d getVelocity() const;
    void setVelocity(const Vec2d &velocity);
    [[nodiscard]] virtual BoundingBox getBoundingBox() const;
protected:
    Location location_;
    Vec2d velocity_;
    bool friction_;
    bool gravity_;
private:
    Task* physicsTask_;
};


#endif //FLATCRAFT_ENTITY_H
