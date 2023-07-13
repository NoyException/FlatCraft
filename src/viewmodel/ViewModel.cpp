//
// Created by Noy on 2023/7/13.
//

#include "ViewModel.h"

bool ViewModel::isBound() const {
    return bound_;
}

void ViewModel::notifyBound() {
    if(!bound_){
        bound_ = true;
        onBound();
    }
}
