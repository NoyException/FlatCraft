//
// Created by Noy on 2023/7/12.
//

#include "DroppedItemViewModel.h"

DroppedItemViewModel::DroppedItemViewModel(DroppedItem *droppedItem) :
EntityViewModel(droppedItem), materialStack_(droppedItem->getItemStack()->toMaterialStack()) {
    listener_ = EventManager::registerListener<ValueChangedNotification<DroppedItem>>(EventPriority::MONITOR,[&](ValueChangedNotification<DroppedItem>* event){
        if(event->getObject()==droppedItem){
            if(event->getField()==Field::DROPPED_ITEM_ITEMSTACK){
                materialStack_ = droppedItem->getItemStack()->toMaterialStack();
                notificationMaterialStackChanged_();
            }
            if(event->getField()==Field::DROPPED_ITEM_STATE){
                if(event->getNewValue<int>()==1) notificationPickedUp_();
                else notificationDisappeared_();
            }
        }
    });
}

DroppedItemViewModel::~DroppedItemViewModel() {
    EventManager::unregisterListener(listener_);
}

DroppedItem *DroppedItemViewModel::getDroppedItem() const {
    return dynamic_cast<DroppedItem*>(entity_);
}

std::function<void(RefPtr<MaterialStack>)> DroppedItemViewModel::getBinderMaterialStack() {
    return [&](RefPtr<MaterialStack> ptr){
        ptr.pointTo(materialStack_);
    };
}

void DroppedItemViewModel::setNotificationMaterialStackChanged(const std::function<void()> &notification) {
    notificationMaterialStackChanged_ = notification;
}

void DroppedItemViewModel::setNotificationPickedUp(const std::function<void()> &notification) {
    notificationPickedUp_ = notification;
}

void DroppedItemViewModel::setNotificationDisappeared(const std::function<void()> &notification) {
    notificationDisappeared_ = notification;
}
