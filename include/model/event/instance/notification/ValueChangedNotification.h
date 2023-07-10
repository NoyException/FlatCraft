//
// Created by Noy on 2023/7/10.
//

#ifndef FLATCRAFT_VALUECHANGEDNOTIFICATION_H
#define FLATCRAFT_VALUECHANGEDNOTIFICATION_H

#include "../../EventType.h"
#include "../EventInstance.h"

class ValueChangedNotification : public EventInstance{
public:
    template<class T>
    ValueChangedNotification(const std::string &key, const T &oldValue, const T &newValue);

    [[nodiscard]] const std::string &getKey() const;

    template<class T>
    [[nodiscard]] const T &getOldValue() const;

    template<class T>
    [[nodiscard]] const T &getNewValue() const;

protected:
    template<class T>
    ValueChangedNotification(const Event *event, const std::string &key,
                             const T &oldValue, const T &newValue);
private:
    std::string key_;
    std::any oldValue_;
    std::any newValue_;
};

template<class T>
ValueChangedNotification::ValueChangedNotification(const std::string &key, const T &oldValue, const T &newValue)
: ValueChangedNotification(EventType::VALUE_NOTIFICATION_EVENT, key, oldValue, newValue){}

template<class T>
ValueChangedNotification::ValueChangedNotification(const Event *event, const std::string &key,
                                                   const T &oldValue, const T &newValue) :
                                     EventInstance(event), key_(key),
                                     oldValue_(std::make_any<T>(oldValue)), newValue_(std::make_any<T>(newValue)) {}

template<class T>
const T &ValueChangedNotification::getOldValue() const {
    return std::any_cast<T>(oldValue_);
}

template<class T>
const T &ValueChangedNotification::getNewValue() const {
    return std::any_cast<T>(newValue_);
}

#endif //FLATCRAFT_VALUECHANGEDNOTIFICATION_H
