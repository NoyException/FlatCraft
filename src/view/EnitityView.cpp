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
        //����Ĵ��뽫��Model֪ͨ��View���λ�÷����ı�ʱ��ִ��

    };
}

std::function<void()> EntityView::getNotificationVelocityChanged() {
    return [&]() {};
}


std::function<void()> EntityView::getNotificationDirectionChanged() {
    return [&]() {};
}