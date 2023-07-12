#include "view/PlayerView.h"

void PlayerView::setCommandChangeCursorPosition(const std::function<void(const Vec2d&)>& command) {
    commandChangeCursorPosition_ = command;
}

//TODO: ʵ�֣�
void PlayerView::setCommandChangeKeyState(const std::function<void(Key, KeyState)>& command) {
    commandChangeKeyState_ = command;
}

//TODO: ʵ�֣�
void PlayerView::setCommandScrollMouseWheel(const std::function<void(double)>& command) {
    commandScrollMouseWheel_ = command;
}



//TODO: ʵ�֣�
void PlayerView::setBinderCurrentSlot(const std::function<void(RefPtr<int>)>& binder) {
    binder(binderSlot_);
}

//TODO: ʵ�֣�


//TODO: ʵ�֣�
void PlayerView::setBinderSneaking(const std::function<void(RefPtr<bool>)>& binder) {
    binder(binderSneak_);
}

//TODO: ʵ�֣�
void PlayerView::setBinderBreakingProgress(const std::function<void(RefPtr<double>)>& binder) {
    binder(binderBreakingProgress_);
}






//TODO: ʵ�֣�
std::function<void()> PlayerView::getNotificationCurrentSlotChanged() {
    return [&]() {};
}

//TODO: ʵ�֣�
std::function<void()> PlayerView::getNotificationBreakingProgressChanged() {
    return [&]() {
        isDigging = true;
    };
}

//TODO: ʵ�֣�
std::function<void()> PlayerView::getNotificationSneakingStateChanged() {
    return [&]() {};
}