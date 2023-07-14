//
// Created by Noy on 2023/7/3.
//

#include "model/entity/LivingEntity.h"

LivingEntity::LivingEntity() : Entity(), health_(20) {
}

LivingEntity::LivingEntity(const nlohmann::json &json) : Entity(json),
health_(json.at("health").get<double>()) {}

std::unique_ptr<nlohmann::json> LivingEntity::serialize() const {
    std::unique_ptr<nlohmann::json> json = Entity::serialize();
    json->emplace("health",health_);
    return json;
}

bool LivingEntity::isDead() const {
    return health_<=0;
}

double LivingEntity::getHealth() const {
    return health_;
}

void LivingEntity::setHealth(double health) {
    bool die = health_>0 && health<=0;
    health_ = health;
    if(die){
        onDie();
    }
}

void LivingEntity::onDie() {}

void LivingEntity::run() {
    Entity::run();
    double y = location_.getY();
    if(y<-32) setHealth(0);
    else if(y<-16) setHealth(health_-2);
    else if(y<0) setHealth(health_-1);
}
