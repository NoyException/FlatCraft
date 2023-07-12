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
void PlayerView::setBinderCurrentSlot(const std::function<void(RefPtr<int>)>& binder) {
    binder(binderSlot_);
}

//TODO: 实现！


//TODO: 实现！
void PlayerView::setBinderSneaking(const std::function<void(RefPtr<bool>)>& binder) {
    binder(binderSneak_);
}

//TODO: 实现！
void PlayerView::setBinderBreakingProgress(const std::function<void(RefPtr<double>)>& binder) {
    binder(binderBreakingProgress_);
}






//TODO: 实现！
std::function<void()> PlayerView::getNotificationCurrentSlotChanged() {
    return [&]() {};
}

//TODO: 实现！
std::function<void()> PlayerView::getNotificationBreakingProgressChanged() {
    return [&]() {
        isDigging = true;
    };
}

//TODO: 实现！
std::function<void()> PlayerView::getNotificationSneakingStateChanged() {
    return [&]() {};
}