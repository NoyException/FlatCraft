//
// Created by Noy on 2023/7/10.
//

#ifndef FLATCRAFT_PLAYERVIEWMODEL_H
#define FLATCRAFT_PLAYERVIEWMODEL_H

#include "EntityViewModel.h"
#include "model/entity/player/Player.h"

class PlayerViewModel : public EntityViewModel{
public:
    explicit PlayerViewModel(Player* player);
    std::function<void(Key,KeyState)> getCommandChangeKeyState();
    std::function<void(double)> getCommandScrollMouseWheel();
    std::function<void(const Vec2d&)> getCommandChangeCursorPosition();

    std::function<void(RefPtr<int>)> getBinderCurrentSlot();
    std::function<void(RefPtr<bool>)> getBinderSneaking();
    std::function<void(RefPtr<double>)> getBinderBreakingProgress();
    std::function<void(RefPtr<MaterialStack>)> getBinderCursor();
    std::function<void(RefPtr<MaterialStack>)> getBinderInventory();

    void setNotificationCurrentSlotChanged(const std::function<void()> &notificationCurrentSlotChanged);
    void setNotificationSneakingStateChanged(const std::function<void()> &notificationSneakingStateChanged);
    void setNotificationBreakingProgressChanged(const std::function<void()> &notificationBreakingProgressChanged);
    void setNotificationCursorChanged(const std::function<void()> &notificationCursorChanged);
    void setNotificationInventoryChanged(const std::function<void(int)> &notificationInventoryChanged);
protected:
    void onBound() override;

private:
    bool isPressed(Key key);
    void control();
    Player* getPlayer();
    KeyState states_[16];
    //滚轮移动量，向上为正，向下为负
    double scrollY_;
    //鼠标点击位置（绝对位置）
    Vec2d cursorPosition_;
    bool isPaused_ = false;
    bool isEscPressedLastTick_ = false;
    MaterialStack cursor_;
    MaterialStack inventory_[46];
    std::function<void()> notificationCurrentSlotChanged_;
    std::function<void()> notificationSneakingStateChanged_;
    std::function<void()> notificationBreakingProgressChanged_;
    std::function<void()> notificationCursorChanged_;
    std::function<void(int)> notificationInventoryChanged_;
};


#endif //FLATCRAFT_PLAYERVIEWMODEL_H
