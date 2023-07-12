#ifndef ENITITY_VIEW_H_
#define ENITITY_VIEW_H_
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mouse.h"
#include "common.h"

class EntityView {
public:
    void setBinderPosition(const std::function<void(RefPtr<Vec2d>)>& binder);

    void setBinderDirection(const std::function<void(RefPtr<Vec2d>)>& binder);

    void setBinderVelocity(const std::function<void(RefPtr<Vec2d>)>& binder);

    std::function<void()> getNotificationDirectionChanged();

    std::function<void()> getNotificationVelocityChanged();

    std::function<void()> getNotificationLocationChanged();

    Vec2d* binderPosition_;
    Vec2d* binderDirection_;
    Vec2d* binderVelocity_;
};

#endif // !ENITITY_VIEW_H_
