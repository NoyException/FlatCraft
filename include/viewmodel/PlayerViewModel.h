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
    ~PlayerViewModel() override;
    std::function<void(Key,KeyState)> getCommandChangeKeyState();
    std::function<void(double)> getCommandScrollMouseWheel();
    std::function<void(const Vec2d&)> getCommandChangeCursorPosition();
    std::function<void(int)> getCommandClickedSlot();

    std::function<void(RefPtr<int>)> getBinderCurrentSlot();
    std::function<void(RefPtr<bool>)> getBinderSneaking();
    std::function<void(RefPtr<Vec2d>, RefPtr<double>)> getBinderBreakingBlock();
    std::function<void(RefPtr<MaterialStack>)> getBinderCursor();
    std::function<void(RefPtr<MaterialStack>)> getBinderInventory();

    void setNotificationCurrentSlotChanged(const std::function<void()> &notificationCurrentSlotChanged);
    void setNotificationSneakingStateChanged(const std::function<void()> &notificationSneakingStateChanged);
    void setNotificationBreakingBlockChanged(const std::function<void()> &notificationBreakingBlockChanged);
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
    bool isEscPressedLastTick_ = false;
    bool isRightClickPressedLastTick_ = false;
    Vec2d breakingPosition_;
    MaterialStack cursor_;
    MaterialStack inventory_[46];
    BaseListener *listener1_,*listener2_;
    std::function<void()> notificationCurrentSlotChanged_;
    std::function<void()> notificationSneakingStateChanged_;
    std::function<void()> notificationBreakingBlockChanged_;
    std::function<void()> notificationCursorChanged_;
    std::function<void(int)> notificationInventoryChanged_;
};


#endif //FLATCRAFT_PLAYERVIEWMODEL_H
