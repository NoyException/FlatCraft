#include "view/PlayerView.h"

void PlayerView::setCommandChangeCursorPosition(const std::function<void(const Vec2d&)>& command) {
    commandChangeCursorPosition_ = command;
}


void PlayerView::setCommandChangeKeyState(const std::function<void(Key, KeyState)>& command) {
    commandChangeKeyState_ = command;
}


void PlayerView::setCommandScrollMouseWheel(const std::function<void(double)>& command) {
    commandScrollMouseWheel_ = command;
}

void PlayerView::setCommandClickedSlot(const std::function<void(int)>& command) {
    commandClickedSlot_ = command;
}

void PlayerView::setBinderCurrentSlot(const std::function<void(RefPtr<int>)>& binder) {
    binder(binderSlot_);
}

void PlayerView::setBinderSneaking(const std::function<void(RefPtr<bool>)>& binder) {
    binder(binderSneak_);
}

void PlayerView::setBinderBreakingProgress(const std::function<void(RefPtr<double>)>& binder) {
    binder(binderBreakingProgress_);
}

void PlayerView::setBinderCursor(const std::function<void(RefPtr<MaterialStack>)>& binder) {
    binder(binderCursor_);
}

void PlayerView::setBinderInventory(const std::function<void(RefPtr<MaterialStack>)>& binder) {
    binder(binderMaterialStack_);
}





std::function<void()> PlayerView::getNotificationCurrentSlotChanged() {
    return [&]() {};
}


std::function<void()> PlayerView::getNotificationBreakingProgressChanged() {
    return [&]() {
        isDigging = true;
    };
}


std::function<void()> PlayerView::getNotificationSneakingStateChanged() {
    return [&]() {};
}

std::function<void()> PlayerView::getNotificationCursorChanged() {
    return [&]() {

    };
}

std::function<void(int)> PlayerView::getNotificationInventoryChanged() {
    return [&](int index) {

    };
}