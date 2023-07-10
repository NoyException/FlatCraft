//
// Created by Noy on 2023/7/4.
//

#include "model/entity/player/Player.h"
#include "model/FlatCraft.h"
#include "model/event/instance/EntityTeleportEvent.h"
#include "viewmodel/WorldModel.h"

Player::Player(const Location &spawnLocation) : LivingEntity(spawnLocation), controller_(&PlayerController::instance_),
model_(&PlayerModel::instance_), currentSlot_(0), cursor_(Material::AIR),
sprinting_(false), sneaking_(false), flying_(false){
    task_ = FlatCraft::getInstance()->getScheduler()->runTaskTimer([&](){
        control();
        updateModel();
    },0,0);

    EventManager::registerListener(EventType::ENTITY_TELEPORT_EVENT,EventPriority::MONITOR,[&](EventInstance* event){
        auto e = dynamic_cast<EntityTeleportEvent*>(event);
        if(!e->isCanceled() && e->getEntity()==this){
            auto target = e->getTargetLocation().getWorld();
            auto old = location_.getWorld();
            if(target!=old){
                if(old != nullptr) old->stop();
                if(target != nullptr) target->run();
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

void Player::control() {
    //飞行
    if(flying_){
        double speed = 0.2;
        if(controller_->getKeyState(Key::CTRL)==KeyState::DOWN)
            speed = 0.4;
        if(controller_->getKeyState(Key::SHIFT)==KeyState::DOWN)
            speed = 0.05;
        if(controller_->getKeyState(Key::UP)==KeyState::DOWN)
            location_.add(0,speed);
        if(controller_->getKeyState(Key::DOWN)==KeyState::DOWN)
            location_.add(0,-speed);
        if(controller_->getKeyState(Key::LEFT)==KeyState::DOWN)
            location_.add(-speed,0);
        if(controller_->getKeyState(Key::RIGHT)==KeyState::DOWN)
            location_.add(speed,0);
        if(controller_->getKeyState(Key::SPACE)==KeyState::UP)
            setFlying(false);
        return;
    }
    //走路
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
    //下蹲边缘检测
    if(onGround && sneaking_ && std::abs(velocity_.getX())<0.1){

        auto aabb = getBoundingBox();
        Location start = location_;
        start.add(velocity_.getX(),aabb.getHeight()/2);
        auto res = getWorld()->rayTrace(start,{0,-1},0.5,aabb.getWidth()/2,aabb.getHeight()/2,
                                        [](Material material){return true;},[](Entity* entity){return false;});
        if(res==nullptr)
            velocity_.setX(0);
    }
    if(stopSprinting) sprinting_ = false;

    //交互
    bool resetBreakingProgress = true;
    if(controller_->getKeyState(Key::LEFT_CLICK)==KeyState::DOWN){
        auto world = getWorld();
        if(world!= nullptr) {
            //攻击暂时省略
            //挖掘
            auto block = world->getBlock(controller_->clickPosition_, true);
            if (MaterialHelper::isAir(block->getMaterial()) || MaterialHelper::isLiquid(block->getMaterial()))
                block = world->getBlock(controller_->clickPosition_, false);
            if(block != nullptr){
                if(block==lastBreaking_){
                    double hardness = MaterialHelper::getHardness(block->getMaterial());
                    if(hardness>0) breakingProgress_+=0.05/hardness;
                    if(hardness==0) breakingProgress_=1;
                    if(hardness<0) breakingProgress_=0;
                    if(breakingProgress_>1.0) breakingProgress_=1.0;
                    if(breakingProgress_==1.0){
                        block->setMaterial(Material::AIR);
                    }
                    resetBreakingProgress = false;

                    direction_ = controller_->clickPosition_-location_.toVec2d();
                }
                else lastBreaking_=block;
            }
        }

//        std::cout<<"click: "<<controller_->clickPosition_<<std::endl;
//        std::cout<<"progress: "<<breakingProgress_<<std::endl;
    }
    else if(controller_->getKeyState(Key::RIGHT_CLICK)==KeyState::DOWN){
        ;
    }
    if(resetBreakingProgress) breakingProgress_ = 0;

    //DEBUG
    if(controller_->getKeyState(Key::SPACE)==KeyState::DOWN)
        setFlying(true);
    //
    if(controller_->getKeyState(Key::RIGHT_CLICK)==KeyState::DOWN){
        controller_->setKeyState(Key::RIGHT_CLICK,KeyState::UP);
        std::cout<<location_<<" "<<velocity_<<" "<<onGround<<std::endl;
//        isOnGround();
    }
}

void Player::updateModel() {
    //更新玩家ViewModel
    model_->position_ = location_.toVec2d();
    model_->direction_ = direction_;
    model_->velocity_ = velocity_;
    model_->sneaking_ = sneaking_;
    model_->currentSlot_ = currentSlot_;
    model_->cursor_ = {cursor_.getMaterial(), cursor_.getAmount()};
    model_->clickPosition_ = controller_->clickPosition_;
    model_->breakingProgress_ = breakingProgress_;
    model_->legAction_ = (velocity_.getX()<0.000001) ? PlayerModel::LegAction::IDLE : (
            sprinting_? PlayerModel::LegAction::SPRINT : PlayerModel::LegAction::WALK);

    //更新世界ViewModel
    auto world = location_.getWorld();
    if(world == nullptr) return;
    std::lock_guard<std::mutex> lock2(WorldModel::instance_.mtx_);

    WorldModel::instance_.cameraPosition_ = location_.toVec2d();
    auto loc = location_.toBlockLocation().toVec2d();
    loc.add(-(int)(WorldModel::MAX_COLUMN/2),(int)(WorldModel::MAX_ROW*0.618));
    WorldModel::instance_.leftUpPosition_ = loc;
    WorldModel::instance_.leftUpPosition_.add(0,1);
    for(int i=0;i<WorldModel::MAX_COLUMN;i++){
        for(int j=0;j<WorldModel::MAX_ROW;j++){
            for(int k=0;k<=1;k++){
                auto block = world->getBlock(loc.getBlockX()+i,loc.getBlockY()-j,k);
                if(block == nullptr) WorldModel::instance_.materials_[i][j][k]=Material::BED_ROCK;
                else WorldModel::instance_.materials_[i][j][k] = block->getMaterial();
            }
        }
    }
    WorldModel::instance_.ticks_ = world->getTicks();
    WorldModel::instance_.weather_ = world->getWeather();
}

void Player::jump() {
    velocity_.setY(0.2);
}

BoundingBox Player::getBoundingBox() const {
    BoundingBox aabb = Entity::getBoundingBox();
    aabb.expand(0.4,0,0.4,1.8);
    return aabb;
}

bool Player::isFlying() const {
    return flying_;
}

void Player::setFlying(bool flying) {
    gravity_ = !flying;
    flying_ = flying;
    velocity_ = {};
}
