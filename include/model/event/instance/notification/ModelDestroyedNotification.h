//
// Created by Noy on 2023/7/12.
//

#ifndef FLATCRAFT_MODELDESTROYEDNOTIFICATION_H
#define FLATCRAFT_MODELDESTROYEDNOTIFICATION_H

#include "../EventInstance.h"
#include "../../EventType.h"

template<class T>
class ModelDestroyedNotification : public EventInstance {
public:
    explicit ModelDestroyedNotification(T *model) : model_(model) {}

    T *getModel() const {
        return model_;
    }

    static Event* getEventType();
private:
    T* model_;
};

template<class T>
Event *ModelDestroyedNotification<T>::getEventType() {
    return EventType::MODEL_DESTROYED_NOTIFICATION;
}


#endif //FLATCRAFT_MODELDESTROYEDNOTIFICATION_H
