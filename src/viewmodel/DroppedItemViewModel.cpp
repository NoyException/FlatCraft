//
// Created by Noy on 2023/7/12.
//

#include "DroppedItemViewModel.h"

DroppedItemViewModel::DroppedItemViewModel(DroppedItem *droppedItem) :
EntityViewModel(droppedItem), materialStack_(droppedItem->getItemStack()->toMaterialStack()), listener_(nullptr) {}

DroppedItemViewModel::~DroppedItemViewModel() {
    if(listener_!=nullptr)
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

void DroppedItemViewModel::onBound() {
    EntityViewModel::onBound();
    listener_ = EventManager::registerListener<ValueChangedNotification<DroppedItem>>(EventPriority::MONITOR,[&](ValueChangedNotification<DroppedItem>* event){
        DroppedItem *item = getDroppedItem();
        if(event->getObject() == item){
            if(event->getField()==Field::DROPPED_ITEM_ITEMSTACK){
                materialStack_ = item->getItemStack()->toMaterialStack();
                notificationMaterialStackChanged_();
            }
            if(event->getField()==Field::DROPPED_ITEM_STATE){
                if(event->getPayload<int>() == 1) notificationPickedUp_();
                else notificationDisappeared_();
            }
        }
    });
}
