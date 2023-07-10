//
// Created by Noy on 2023/7/6.
//

#include "model/event/Cancelable.h"

void Cancelable::setCanceled(bool canceled) {
    canceled_ = canceled;
}

bool Cancelable::isCanceled() const {
    return canceled_;
}
