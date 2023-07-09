//
// Created by Noy on 2023/7/6.
//

#ifndef FLATCRAFT_PLAYERCONTROLLER_H
#define FLATCRAFT_PLAYERCONTROLLER_H

#include <optional>
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
    [[nodiscard]] const std::optional<Vec2d> &getLeftClickPosition() const;
    void setLeftClickPosition(const std::optional<Vec2d> &leftClickPosition);
    [[nodiscard]] const std::optional<Vec2d> &getRightClickPosition() const;
    void setRightClickPosition(const std::optional<Vec2d> &rightClickPosition);
    void reset();
    static PlayerController instance_;
    friend class Player;
private:
    KeyState states_[16];
    //滚轮移动量，向上为正，向下为负
    double wheelY_;
    //鼠标点击位置（绝对位置）
    std::optional<Vec2d> leftClickPosition_;
    std::optional<Vec2d> rightClickPosition_;
};


#endif //FLATCRAFT_PLAYERCONTROLLER_H
