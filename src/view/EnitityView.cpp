#include "view/EnitityView.h"

void EntityView::setBinderVelocity(const std::function<void(RefPtr<Vec2d>)>& binder) {
    binder(binderVelocity_);
}


void EntityView::setBinderPosition(const std::function<void(RefPtr<Vec2d>)>& binder) {
    binder(binderPosition_);
}

void EntityView::setBinderDirection(const std::function<void(RefPtr<Vec2d>)>& binder) {
    binder(binderDirection_);
}

std::function<void()> EntityView::getNotificationLocationChanged() {
    return [&]() {
        //这里的代码将在Model通知该View玩家位置发生改变时被执行

    };
}

std::function<void()> EntityView::getNotificationVelocityChanged() {
    return [&]() {};
}


std::function<void()> EntityView::getNotificationDirectionChanged() {
    return [&]() {};
}