//
// Created by Noy on 2023/7/10.
//

#include "EntityViewModel.h"
#include "model/event/events.h"

EntityViewModel::EntityViewModel(Entity *entity) : entity_(entity) {
    EventManager::registerListener(EventType::ENTITY_LOCATION_CHANGED_NOTIFICATION, EventPriority::MONITOR,
                                   [&](EventInstance *event){
                                       auto entity = dynamic_cast<EntityNotification*>(event)->getEntity();
                                       if(entity == entity_) notificationLocationChanged_();
                                   });
    EventManager::registerListener(EventType::ENTITY_LOCATION_CHANGED_NOTIFICATION, EventPriority::MONITOR,
                                   [&](EventInstance *event){
                                       auto entity = dynamic_cast<EntityNotification*>(event)->getEntity();
                                       if(entity == entity_) notificationDirectionChanged_();
                                   });
    EventManager::registerListener(EventType::ENTITY_VELOCITY_CHANGED_NOTIFICATION, EventPriority::MONITOR,
                                   [&](EventInstance *event){
                                       auto entity = dynamic_cast<EntityNotification*>(event)->getEntity();
                                       if(entity == entity_) notificationVelocityChanged_();
                                   });
}

std::function<Vec2d()> EntityViewModel::getBinderLocation() {
    return [&](){
        return entity_->getLocation().toVec2d();
    };
}

std::function<Vec2d()> EntityViewModel::getBinderDirection() {
    return [&](){
        return entity_->getDirection();
    };
}

std::function<Vec2d()> EntityViewModel::getBinderVelocity() {
    return [&](){
        return entity_->getVelocity();
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

