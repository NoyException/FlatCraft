//
// Created by Noy on 2023/7/3.
//

#ifndef FLATCRAFT_ENTITY_H
#define FLATCRAFT_ENTITY_H

#include "common.h"
#include "model/Location.h"
#include "model/scheduler/Task.h"

/**
 * 从FlatCraft创建Entity，然后调用teleport进行召唤
 */
class Entity {
public:
    friend class FlatCraft;
    friend class EntityViewModel;
//    friend class World;
    Entity();
    virtual ~Entity();
    explicit Entity(const nlohmann::json& json);
    [[nodiscard]] virtual std::unique_ptr<nlohmann::json> serialize() const;
    static std::unique_ptr<Entity> deserialize(const nlohmann::json& json);
    [[nodiscard]] int getId() const;
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
    [[nodiscard]] bool isSpawned() const;
    [[nodiscard]] virtual EntityType getType() const = 0;
    virtual void remove();
protected:
    virtual void run();
    virtual void notifyJoinWorld(World *world);
    virtual void notifyLeaveWorld(World *world);
    int id_;
    Location location_;
    Vec2d direction_;
    Vec2d velocity_;
    bool friction_;
    bool gravity_;
private:
    Task* physicsTask_;
};


#endif //FLATCRAFT_ENTITY_H
