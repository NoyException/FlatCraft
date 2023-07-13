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

    void setCommandClickedSlot(const std::function<void(int)>& command);

    

    void setBinderCurrentSlot(const std::function<void(RefPtr<int>)>& binder);

    void setBinderSneaking(const std::function<void(RefPtr<bool>)>& binder);

    void setBinderBreakingProgress(const std::function<void(RefPtr<double>)>& binder);

    void setBinderCursor(const std::function<void(RefPtr<MaterialStack>)>& binder);

    void setBinderInventory(const std::function<void(RefPtr<MaterialStack>)>& binder);
    

    std::function<void()> getNotificationCurrentSlotChanged();

    

    std::function<void()> getNotificationSneakingStateChanged();

    std::function<void()> getNotificationBreakingProgressChanged();

    std::function<void()> getNotificationCursorChanged();

    std::function<void(int)> getNotificationInventoryChanged();

    std::function<void(const Vec2d&)> commandChangeCursorPosition_;
    std::function<void(Key, KeyState)> commandChangeKeyState_;
    std::function<void(double)> commandScrollMouseWheel_;
    std::function<void(int)> commandClickedSlot_;
    
    int* binderSlot_;
    bool* binderSneak_;
    double* binderBreakingProgress_;
    bool isDigging;
    MaterialStack* binderMaterialStack_;//46
    MaterialStack* binderCursor_;
};

#endif
