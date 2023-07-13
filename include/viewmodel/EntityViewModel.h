//
// Created by Noy on 2023/7/10.
//

#ifndef FLATCRAFT_ENTITYVIEWMODEL_H
#define FLATCRAFT_ENTITYVIEWMODEL_H

#include "common.h"
#include "ViewModel.h"
#include "model/entity/entities.h"

class EntityViewModel : public ViewModel {
public:
    explicit EntityViewModel(Entity* entity);

    std::function<void(RefPtr<Vec2d>)> getBinderPosition();
    std::function<void(RefPtr<Vec2d>)> getBinderDirection();
    std::function<void(RefPtr<Vec2d>)> getBinderVelocity();

    void setNotificationLocationChanged(const std::function<void()> &notification);
    void setNotificationDirectionChanged(const std::function<void()> &notification);
    void setNotificationVelocityChanged(const std::function<void()> &notification);

protected:
    void onBound() override;

    Entity* entity_;
    Vec2d position_;

private:
    std::function<void()> notificationLocationChanged_;
    std::function<void()> notificationDirectionChanged_;
    std::function<void()> notificationVelocityChanged_;
};

#endif //FLATCRAFT_ENTITYVIEWMODEL_H
