#ifndef _PLAYERVIEW_H_
#define _PLAYERVIEW_H_
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mouse.h"
#include "common.h"

class PlayerView {
public:
    void setCommandChangeCursorPosition(const std::function<void(const Vec2d&)>& command);

    void setCommandChangeKeyState(const std::function<void(Key, KeyState)>& command);

    void setCommandScrollMouseWheel(const std::function<void(double)>& command);

    void setBinderLocation(const std::function<Vec2d()>& binder);

    void setBinderDirection(const std::function<Vec2d()>& binder);

    void setBinderVelocity(const std::function<Vec2d()>& binder);

    void setBinderCurrentSlot(const std::function<int()>& binder);

    void setBinderSneaking(const std::function<bool()>& binder);

    void setBinderBreakingProgress(const std::function<double()>& binder);

    std::function<void()> getNotificationDirectionChanged();

    std::function<void()> getNotificationVelocityChanged();

    std::function<void()> getNotificationCurrentSlotChanged();

    std::function<void()> getNotificationLocationChanged();

    std::function<void()> getNotificationSneakingStateChanged();

    std::function<void()> getNotificationBreakingProgressChanged();
private:
    std::function<void(const Vec2d&)> commandChangeCursorPosition_;
    std::function<void(Key, KeyState)> commandChangeKeyState_;
    std::function<void(double)> commandScrollMouseWheel_;


};

#endif
