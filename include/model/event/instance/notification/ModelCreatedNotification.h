//
// Created by Noy on 2023/7/12.
//

#ifndef FLATCRAFT_MODELCREATEDNOTIFICATION_H
#define FLATCRAFT_MODELCREATEDNOTIFICATION_H

#include "../EventInstance.h"
#include "../../EventType.h"

/**
 * 用于提醒中途生成了新的ViewModel
 */
template<class T>
class ModelCreatedNotification : public EventInstance {
public:
    explicit ModelCreatedNotification(T *model) : model_(model) {}

    T *getModel() const {
        return model_;
    }

    static Event* getEventType();
private:
    T* model_;
};

template<class T>
Event *ModelCreatedNotification<T>::getEventType() {
    return EventType::MODEL_CREATED_NOTIFICATION;
}


#endif //FLATCRAFT_MODELCREATEDNOTIFICATION_H
