//
// Created by Noy on 2023/7/10.
//

#ifndef FLATCRAFT_VALUECHANGEDNOTIFICATION_H
#define FLATCRAFT_VALUECHANGEDNOTIFICATION_H

#include "../../EventType.h"
#include "../EventInstance.h"

enum class Field{
    ENTITY_POSITION,
    ENTITY_DIRECTION,
    ENTITY_VELOCITY,
    WORLD_TICKS,
    WORLD_WEATHER,
    DROPPED_ITEM_ITEMSTACK,
    DROPPED_ITEM_STATE,
    PLAYER_CURSOR,
    PLAYER_INVENTORY,
    PLAYER_CURRENT_SLOT,
};

template<class T>
class ValueChangedNotification : public EventInstance{
public:
    template<class V>
    ValueChangedNotification(T* obj, Field field, const V &newValue);

    [[nodiscard]] T* getObject() const;

    [[nodiscard]] Field getField() const;

    template<class V>
    [[nodiscard]] V getPayload() const;

    static Event* getEventType();

private:
    T* object_;
    Field field_;
    std::any payload_;
};

template<class T>
Event *ValueChangedNotification<T>::getEventType() {
    return EventType::VALUE_CHANGED_NOTIFICATION;
}

template<class T>
template<class V>
ValueChangedNotification<T>::ValueChangedNotification(T *obj, Field field, const V &newValue)
        : object_(obj), field_(field),
          payload_(std::make_any<V>(newValue)){}

template<class T>
T* ValueChangedNotification<T>::getObject() const{
    return object_;
}

template<class T>
Field ValueChangedNotification<T>::getField() const {
    return field_;
}

template<class T>
template<class V>
V ValueChangedNotification<T>::getPayload() const {
    return std::any_cast<V>(payload_);
}

#endif //FLATCRAFT_VALUECHANGEDNOTIFICATION_H
