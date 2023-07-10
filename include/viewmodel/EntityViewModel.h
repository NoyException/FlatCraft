//
// Created by Noy on 2023/7/10.
//

#ifndef FLATCRAFT_ENTITYVIEWMODEL_H
#define FLATCRAFT_ENTITYVIEWMODEL_H

#include "common.h"
#include "model/entity/Entity.h"

class EntityViewModel {
public:
    explicit EntityViewModel(Entity* entity);

    std::function<Vec2d()> getBinderLocation();
    std::function<Vec2d()> getBinderDirection();
    std::function<Vec2d()> getBinderVelocity();

    void setNotificationLocationChanged(const std::function<void()> &notification);
    void setNotificationDirectionChanged(const std::function<void()> &notification);
    void setNotificationVelocityChanged(const std::function<void()> &notification);

protected:
    Entity* entity_;

private:
    std::function<void()> notificationLocationChanged_;
    std::function<void()> notificationDirectionChanged_;
    std::function<void()> notificationVelocityChanged_;
};

#endif //FLATCRAFT_ENTITYVIEWMODEL_H
