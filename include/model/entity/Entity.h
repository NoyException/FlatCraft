//
// Created by Noy on 2023/7/3.
//

#ifndef FLATCRAFT_ENTITY_H
#define FLATCRAFT_ENTITY_H

#include "common.h"
#include "Location.h"
#include "model/scheduler/Task.h"

class Entity {
public:
    friend class EntityViewModel;
    explicit Entity(const Location& spawnLocation, const Vec2d& direction = {1,0});
    virtual ~Entity();
    [[nodiscard]] virtual nlohmann::json serialize() const;
    [[nodiscard]] Location getLocation() const;
    [[nodiscard]] World* getWorld() const;
    void teleport(const Location& location);
    [[nodiscard]] Vec2d getDirection() const;
    void setDirection(const Vec2d &direction);
    [[nodiscard]] Vec2d getVelocity() const;
    void setVelocity(const Vec2d &velocity);
    void move();
    void move(const Vec2d& v);
    [[nodiscard]] bool hasFriction() const;
    [[nodiscard]] bool hasGravity() const;
    [[nodiscard]] bool isOnGround() const;
    [[nodiscard]] bool isCollided(BoundingBox::Face face) const;
    [[nodiscard]] virtual BoundingBox getBoundingBox() const;
protected:
    Location location_;
    Vec2d direction_;
    Vec2d velocity_;
    bool friction_;
    bool gravity_;
private:
    Task* physicsTask_;
};


#endif //FLATCRAFT_ENTITY_H
