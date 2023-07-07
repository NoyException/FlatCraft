//
// Created by Noy on 2023/7/6.
//

#ifndef FLATCRAFT_PLAYERCONTROLLER_H
#define FLATCRAFT_PLAYERCONTROLLER_H

#include "common.h"

class PlayerController {
public:
    void up();
    void down();
    void left();
    void right();
    void space();
    void shift();
    void ctrl();
    void leftClick();
    void rightClick();
    void reset();
    friend class Player;
private:
    bool up_;
    bool down_;
    bool left_;
    bool right_;
    bool space_;
    bool shift_;
    bool ctrl_;
    bool leftClick_;
    bool rightClick_;
    bool locked_;
};


#endif //FLATCRAFT_PLAYERCONTROLLER_H
