//
// Created by Noy on 2023/7/9.
//

#include "PlayerModel.h"

PlayerModel::PlayerModel() : EntityModel(EntityType::PLAYER), sneaking_(false),
cursor_({Material::AIR,1}), actionBar_(), currentSlot_(0),
handAction_(HandAction::IDLE), legAction_(LegAction::IDLE){
    for (auto &item: actionBar_){
        item = {Material::AIR,1};
    }
}

PlayerModel PlayerModel::instance_;
