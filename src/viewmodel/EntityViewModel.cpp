//
// Created by Noy on 2023/7/10.
//

#include "EntityViewModel.h"

EntityViewModel::EntityViewModel(Entity *entity) : entity_(entity), listener_(nullptr) {}

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

void EntityViewModel::setNotificationPositionChanged(const std::function<void()> &notification) {
    notificationPositionChanged_ = notification;
}

void EntityViewModel::setNotificationDirectionChanged(const std::function<void()> &notification) {
    notificationDirectionChanged_ = notification;
}

void EntityViewModel::setNotificationVelocityChanged(const std::function<void()> &notification) {
    notificationVelocityChanged_ = notification;
}

void EntityViewModel::onBound() {
    listener_ = EventManager::registerListener<ValueChangedNotification<Entity>>(EventPriority::MONITOR, [&](auto *event) {
        if (event != nullptr && event->getObject() == entity_) {
            switch (event->getField()) {
                case Field::ENTITY_POSITION:
                    position_ = entity_->getLocation().toVec2d();
                    notificationPositionChanged_();
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

EntityViewModel::~EntityViewModel() {
    if(listener_!=nullptr){
        EventManager::unregisterListener(listener_);
    }
}

