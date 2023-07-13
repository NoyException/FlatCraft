//
// Created by Noy on 2023/7/12.
//

#ifndef FLATCRAFT_DROPPEDITEMVIEWMODEL_H
#define FLATCRAFT_DROPPEDITEMVIEWMODEL_H

#include "EntityViewModel.h"
#include "model/event/events.h"

class DroppedItemViewModel : public EntityViewModel {
public:
    explicit DroppedItemViewModel(DroppedItem *droppedItem);
    ~DroppedItemViewModel();
    std::function<void(RefPtr<MaterialStack>)> getBinderMaterialStack();
    void setNotificationMaterialStackChanged(const std::function<void()> &notification);
    void setNotificationPickedUp(const std::function<void()> &notification);
    void setNotificationDisappeared(const std::function<void()> &notification);
    [[nodiscard]] DroppedItem* getDroppedItem() const;
protected:
    void onBound() override;

private:
    BaseListener* listener_;
    MaterialStack materialStack_;
    std::function<void()> notificationMaterialStackChanged_;
    std::function<void()> notificationPickedUp_;
    std::function<void()> notificationDisappeared_;
};


#endif //FLATCRAFT_DROPPEDITEMVIEWMODEL_H
