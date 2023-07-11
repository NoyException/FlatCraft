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
void PlayerView::setBinderLocation(const std::function<Vec2d()>& binder) {

}

//TODO: ʵ�֣�
void PlayerView::setBinderDirection(const std::function<Vec2d()>& binder) {

}

//TODO: ʵ�֣�
void PlayerView::setBinderCurrentSlot(const std::function<int()>& binder) {

}

//TODO: ʵ�֣�
void PlayerView::setBinderVelocity(const std::function<Vec2d()>& binder) {

}

//TODO: ʵ�֣�
void PlayerView::setBinderSneaking(const std::function<bool()>& binder) {

}

//TODO: ʵ�֣�
void PlayerView::setBinderBreakingProgress(const std::function<double()>& binder) {

}

//TODO: ʵ�֣�
std::function<void()> PlayerView::getNotificationLocationChanged() {
    return [&]() {
        //����Ĵ��뽫��Model֪ͨ��View���λ�÷����ı�ʱ��ִ��

    };
}

//TODO: ʵ�֣�
std::function<void()> PlayerView::getNotificationVelocityChanged() {
    return [&]() {};
}

//TODO: ʵ�֣�
std::function<void()> PlayerView::getNotificationDirectionChanged() {
    return [&]() {};
}

//TODO: ʵ�֣�
std::function<void()> PlayerView::getNotificationCurrentSlotChanged() {
    return [&]() {};
}

//TODO: ʵ�֣�
std::function<void()> PlayerView::getNotificationBreakingProgressChanged() {
    return [&]() {};
}

//TODO: ʵ�֣�
std::function<void()> PlayerView::getNotificationSneakingStateChanged() {
    return [&]() {};
}