//
// Created by Noy on 2023/7/9.
//

#ifndef FLATCRAFT_PLAYERMODEL_H
#define FLATCRAFT_PLAYERMODEL_H

#include "Material.h"
#include "EntityModel.h"
#include "ItemModel.h"

class PlayerModel : public EntityModel{
public:
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
        WALK,
        //疾跑
        SPRINT,
    };
    PlayerModel();
    //玩家是否下蹲
    bool sneaking_;
    //玩家鼠标所持物品
    ItemModel cursor_;
    //玩家行动栏的物品（下面的一排）
    ItemModel actionBar_[9];
    //玩家的手正持有行动栏的第几个格子
    int currentSlot_;
    HandAction handAction_;
    LegAction legAction_;
    Vec2d clickPosition_;
    double breakingProgress_;
    static PlayerModel instance_;
};


#endif //FLATCRAFT_PLAYERMODEL_H
