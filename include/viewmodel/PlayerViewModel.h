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

    std::function<int()> getBinderCurrentSlot();
    std::function<bool()> getBinderSneaking();
    std::function<double()> getBinderBreakingProgress();

    void setNotificationCurrentSlotChanged(const std::function<void()> &notificationCurrentSlotChanged);
    void setNotificationSneakingStateChanged(const std::function<void()> &notificationSneakingStateChanged);
    void setNotificationBreakingProgressChanged(const std::function<void()> &notificationBreakingProgressChanged);

private:
    bool isPressed(Key key);
    void control();
    Player* getPlayer();
    KeyState states_[16];
    //滚轮移动量，向上为正，向下为负
    double scrollY_;
    //鼠标点击位置（绝对位置）
    Vec2d cursorPosition_;
    std::function<void()> notificationCurrentSlotChanged_;
    std::function<void()> notificationSneakingStateChanged_;
    std::function<void()> notificationBreakingProgressChanged_;
};


#endif //FLATCRAFT_PLAYERVIEWMODEL_H
