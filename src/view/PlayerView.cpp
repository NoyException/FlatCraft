#include "view/PlayerView.h"

void PlayerView::setCommandChangeCursorPosition(const std::function<void(const Vec2d&)>& command) {
    commandChangeCursorPosition_ = command;
}

//TODO: 实现！
void PlayerView::setCommandChangeKeyState(const std::function<void(Key, KeyState)>& command) {
    commandChangeKeyState_ = command;
}

//TODO: 实现！
void PlayerView::setCommandScrollMouseWheel(const std::function<void(double)>& command) {
    commandScrollMouseWheel_ = command;
}

//TODO: 实现！
void PlayerView::setBinderLocation(const std::function<Vec2d()>& binder) {

}

//TODO: 实现！
void PlayerView::setBinderDirection(const std::function<Vec2d()>& binder) {

}

//TODO: 实现！
void PlayerView::setBinderCurrentSlot(const std::function<int()>& binder) {

}

//TODO: 实现！
void PlayerView::setBinderVelocity(const std::function<Vec2d()>& binder) {

}

//TODO: 实现！
void PlayerView::setBinderSneaking(const std::function<bool()>& binder) {

}

//TODO: 实现！
void PlayerView::setBinderBreakingProgress(const std::function<double()>& binder) {

}

//TODO: 实现！
std::function<void()> PlayerView::getNotificationLocationChanged() {
    return [&]() {
        //这里的代码将在Model通知该View玩家位置发生改变时被执行

    };
}

//TODO: 实现！
std::function<void()> PlayerView::getNotificationVelocityChanged() {
    return [&]() {};
}

//TODO: 实现！
std::function<void()> PlayerView::getNotificationDirectionChanged() {
    return [&]() {};
}

//TODO: 实现！
std::function<void()> PlayerView::getNotificationCurrentSlotChanged() {
    return [&]() {};
}

//TODO: 实现！
std::function<void()> PlayerView::getNotificationBreakingProgressChanged() {
    return [&]() {};
}

//TODO: 实现！
std::function<void()> PlayerView::getNotificationSneakingStateChanged() {
    return [&]() {};
}