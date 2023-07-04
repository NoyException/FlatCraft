//
// Created by Noy on 2023/7/3.
//

#ifndef FLATCRAFT_LIVINGENTITY_H
#define FLATCRAFT_LIVINGENTITY_H

#include "common.h"
#include "Entity.h"

class LivingEntity : public Entity {
public:
    explicit LivingEntity(const Location& spawnLocation);
    [[nodiscard]] bool isDead() const;
private:
    double health_;
};


#endif //FLATCRAFT_LIVINGENTITY_H