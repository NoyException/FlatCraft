//
// Created by Noy on 2023/7/10.
//

#include "EntityViewModel.h"
#include "model/event/events.h"

EntityViewModel::EntityViewModel(Entity *entity) : entity_(entity) {

    EventManager::registerListener(EventType::VALUE_CHANGED_NOTIFICATION, EventPriority::MONITOR,[&](EventInstance *event) {
        auto e = dynamic_cast<ValueChangedNotification<Entity> *>(event);
        if (e != nullptr && e->getObject() == entity_) {
            switch (e->getField()) {
                case Field::ENTITY_POSITION:
                    position_ = entity_->getLocation().toVec2d();
                    notificationLocationChanged_();
                    break;
                case Field::ENTITY_DIRECTION:
                    notificationDirectionChanged_();
                    break;
                case Field::ENTITY_VELOCITY:
                    notificationVelocityChanged_();
                    break;
                default:
                    break;
            }
        }
    });
}

std::function<void(RefPtr<Vec2d>)> EntityViewModel::getBinderPosition() {
    return [&](RefPtr<Vec2d> ptr){
        ptr.pointTo(position_);
    };
}

std::function<void(RefPtr<Vec2d>)> EntityViewModel::getBinderDirection() {
    return [&](RefPtr<Vec2d> ptr){
        ptr.pointTo(entity_->direction_);
    };
}

std::function<void(RefPtr<Vec2d>)> EntityViewModel::getBinderVelocity() {
    return [&](RefPtr<Vec2d> ptr){
        ptr.pointTo(entity_->velocity_);
    };
}

void EntityViewModel::setNotificationLocationChanged(const std::function<void()> &notification) {
    notificationLocationChanged_ = notification;
}

void EntityViewModel::setNotificationDirectionChanged(const std::function<void()> &notification) {
    notificationDirectionChanged_ = notification;
}

void EntityViewModel::setNotificationVelocityChanged(const std::function<void()> &notification) {
    notificationVelocityChanged_ = notification;
}

