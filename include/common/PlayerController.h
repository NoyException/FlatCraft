//
// Created by Noy on 2023/7/6.
//

#ifndef FLATCRAFT_PLAYERCONTROLLER_H
#define FLATCRAFT_PLAYERCONTROLLER_H

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
    void reset();
    static PlayerController instance_;
    friend class Player;
private:
    KeyState states_[16];
};


#endif //FLATCRAFT_PLAYERCONTROLLER_H
