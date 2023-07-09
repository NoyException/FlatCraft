//
// Created by Noy on 2023/7/6.
//

#ifndef FLATCRAFT_PLAYERCONTROLLER_H
#define FLATCRAFT_PLAYERCONTROLLER_H

#include "Vec2d.h"

enum class Key : int{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    SPACE,
    SHIFT,
    CTRL,
    LEFT_CLICK,
    RIGHT_CLICK,
};

enum class KeyState : bool{
    UP,
    DOWN,
};

class PlayerController {
public:
    PlayerController();
    void setKeyState(Key key, KeyState state);
    [[nodiscard]] KeyState getKeyState(Key key) const;
    [[nodiscard]] double getWheelY() const;
    void setWheelY(double wheelY);
    [[nodiscard]] const Vec2d &getClickPosition() const;
    void setClickPosition(const Vec2d &clickPosition);
    void reset();
    static PlayerController instance_;
    friend class Player;
private:
    KeyState states_[16];
    //滚轮移动量，向上为正，向下为负
    double wheelY_;
    //鼠标点击位置（绝对位置）
    Vec2d clickPosition_;
};


#endif //FLATCRAFT_PLAYERCONTROLLER_H
