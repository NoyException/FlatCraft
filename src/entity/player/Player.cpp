//
// Created by Noy on 2023/7/4.
//

#include "entity/player/Player.h"
#include "common/PlayerController.h"
#include "FlatCraft.h"
#include "event/instance/EntityTeleportEvent.h"

Player::Player(const Location &spawnLocation) : LivingEntity(spawnLocation), controller_(&PlayerController::instance_) {
    task_ = FlatCraft::getInstance()->getScheduler()->runTaskTimer([&](){

        bool onGround = isOnGround();
        if(controller_->getKeyState(Key::CTRL)==KeyState::DOWN){
            sprinting_ = true;
        }
        if(controller_->getKeyState(Key::SHIFT)==KeyState::DOWN){
            sprinting_ = false;
            sneaking_ = true;
        }
        else sneaking_ = false;
        if(controller_->getKeyState(Key::UP)==KeyState::DOWN){
            if(onGround) jump();
        }
        double dx = onGround ? 0.2 : 0.05;
        if(sprinting_) dx*=1.5;
        if(sneaking_) dx*=0.3;
        bool stopSprinting;
        if(controller_->getKeyState(Key::LEFT)==KeyState::DOWN && controller_->getKeyState(Key::RIGHT)==KeyState::UP){
            if(onGround){
                velocity_.setX(std::max(-dx,velocity_.getX()-0.08));
            }
            else if(velocity_.getX()>-dx){
                velocity_.setX(std::max(-dx,velocity_.getX()-0.02));
            }
            friction_ = false;
            stopSprinting = false;
        }
        else if(controller_->getKeyState(Key::RIGHT)==KeyState::DOWN && controller_->getKeyState(Key::LEFT)==KeyState::UP){
            if(onGround){
                velocity_.setX(std::min(dx,velocity_.getX()+0.08));
            }
            else if(velocity_.getX()<dx){
                velocity_.setX(std::min(dx,velocity_.getX()+0.02));
            }
            friction_ = false;
            stopSprinting = false;
        }
        else{
            friction_ = true;
            stopSprinting = true;
        }
        if(stopSprinting) sprinting_ = false;
        //controller_->reset();

        if(controller_->getKeyState(Key::SPACE)==KeyState::DOWN){
            controller_->setKeyState(Key::SPACE,KeyState::UP);
//            onGround = isOnGround();
            std::cout<<location_<<" "<<velocity_<<std::endl;
        }

        updateModel();
    },0,0);

    EventManager::registerListener(EventManager::ENTITY_TELEPORT_EVENT,EventPriority::MONITOR,[&](EventInstance* event){
        auto e = dynamic_cast<EntityTeleportEvent*>(event);
        if(!e->isCanceled() && e->getEntity()==this){
            auto target = e->getTargetLocation().getWorld();
            if(target!=location_.getWorld()){
                location_.getWorld()->stop();
                target->run();
            }
        }
    });
}

Player::~Player() {
    task_->cancel();
}

nlohmann::json Player::serialize() const {
    return std::move(LivingEntity::serialize());
}

std::unique_ptr<Player> Player::deserialize(const nlohmann::json &json) {
    auto player = std::make_unique<Player>(Location::deserialize(json.at("location")));
    player->health_ = json.at("health").get<double>();
    return std::move(player);
}

PlayerController *Player::getController() {
    return controller_;
}

void Player::updateModel() {
    auto world = location_.getWorld();
    if(world == nullptr) return;
    std::lock_guard<std::mutex> lock(WorldModel::instance_.mtx_);

    WorldModel::instance_.cameraPosition_ = location_.toVec2d();
    auto loc = location_.toBlockLocation().toVec2d();
    loc.add(-(int)(WorldModel::MAX_COLUMN/2),(int)(WorldModel::MAX_ROW*0.618));
    WorldModel::instance_.leftUpPosition_ = loc;
    for(int i=0;i<WorldModel::MAX_COLUMN;i++){
        for(int j=0;j<WorldModel::MAX_ROW;j++){
            for(int k=0;k<=1;k++){
                auto block = world->getBlock((int)loc.getX()+i,(int)loc.getY()-j,k);
                if(block == nullptr) WorldModel::instance_.materials_[i][j][k]=Material::BED_ROCK;
                else WorldModel::instance_.materials_[i][j][k] = block->getMaterial();
            }
        }
    }
    WorldModel::instance_.ticks_ = world->getTicks();
}

void Player::jump() {
    velocity_.setY(0.2);
}

BoundingBox Player::getBoundingBox() const {
    BoundingBox aabb = Entity::getBoundingBox();
    aabb.expand(0.4,0,0.4,1.8);
    return aabb;
}
