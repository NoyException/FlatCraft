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
};

template<class T>
class ValueChangedNotification : public EventInstance{
public:
    template<class V>
    ValueChangedNotification(T* obj, Field field, const V &newValue);

    [[nodiscard]] T* getObject() const;

    [[nodiscard]] Field getField() const;

    template<class V>
    [[nodiscard]] V getNewValue() const;

private:
    T* object_;
    Field field_;
    std::any newValue_;
};

template<class T>
template<class V>
ValueChangedNotification<T>::ValueChangedNotification(T *obj, Field field, const V &oldValue, const V &newValue)
        : EventInstance(EventType::VALUE_CHANGED_NOTIFICATION), object_(obj), field_(field),
        newValue_(std::make_any<V>(newValue)){}

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
V ValueChangedNotification<T>::getNewValue() const {
    return std::any_cast<V>(newValue_);
}

#endif //FLATCRAFT_VALUECHANGEDNOTIFICATION_H
