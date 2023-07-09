//
// Created by Noy on 2023/7/9.
//

#ifndef FLATCRAFT_PLAYERMODEL_H
#define FLATCRAFT_PLAYERMODEL_H

#include "Vec2d.h"
#include "Material.h"

class PlayerModel {
    enum class HandAction : int{
        IDLE,
        ATTACK,
        //挖掘
        MINE,
    };
    enum class LegAction : int{
        IDLE,
        //跳跃，不用view做任何动画
        JUMP,
        SNEAK,
        WALK,
        //疾跑
        SPRINT,
    };
    //玩家是否下蹲
    bool sneaking_;
    //玩家所在位置
    Vec2d position_;
    //玩家移动速度
    Vec2d velocity_;
    //玩家鼠标所持物品
    Material cursor_;
    //玩家行动栏的物品（下面的一排）
    Material actionBar_[9];
    //玩家的手正持有行动栏的第几个格子
    int currentSlot_;
    HandAction handAction_;
    LegAction legAction_;
};


#endif //FLATCRAFT_PLAYERMODEL_H
