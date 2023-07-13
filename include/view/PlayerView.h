#ifndef _PLAYERVIEW_H_
#define _PLAYERVIEW_H_
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mouse.h"
#include "common.h"
#include "view/EnitityView.h"

class PlayerView : public EntityView{
public:
    void setCommandChangeCursorPosition(const std::function<void(const Vec2d&)>& command);

    void setCommandChangeKeyState(const std::function<void(Key, KeyState)>& command);

    void setCommandScrollMouseWheel(const std::function<void(double)>& command);

    

    void setBinderCurrentSlot(const std::function<void(RefPtr<int>)>& binder);

    void setBinderSneaking(const std::function<void(RefPtr<bool>)>& binder);

    void setBinderBreakingProgress(const std::function<void(RefPtr<double>)>& binder);

    

    std::function<void()> getNotificationCurrentSlotChanged();

    

    std::function<void()> getNotificationSneakingStateChanged();

    std::function<void()> getNotificationBreakingProgressChanged();

    std::function<void(const Vec2d&)> commandChangeCursorPosition_;
    std::function<void(Key, KeyState)> commandChangeKeyState_;
    std::function<void(double)> commandScrollMouseWheel_;
    
    int* binderSlot_;
    bool* binderSneak_;
    double* binderBreakingProgress_;
    bool isDigging;
    MaterialStack* binderMaterialStack;//46
};

#endif
