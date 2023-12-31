//
// Created by Noy on 2023/7/3.
//

#ifndef FLATCRAFT_LIVINGENTITY_H
#define FLATCRAFT_LIVINGENTITY_H

#include "common.h"
#include "Entity.h"

class LivingEntity : public Entity {
public:
    LivingEntity();
    explicit LivingEntity(const nlohmann::json& json);
    [[nodiscard]] std::unique_ptr<nlohmann::json> serialize() const override;
    ~LivingEntity() override = default;
    [[nodiscard]] double getHealth() const;
    void setHealth(double health);
    [[nodiscard]] bool isDead() const;

protected:
    void run() override;

    virtual void onDie();
    double health_;
};


#endif //FLATCRAFT_LIVINGENTITY_H
