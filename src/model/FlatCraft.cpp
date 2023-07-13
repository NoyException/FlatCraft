//
// Created by Noy on 2023/7/4.
//

#include "model/FlatCraft.h"
#include "model/item/Item.h"
//#include <windows.h>
#include <filesystem>

FlatCraft::FlatCraft() : ticks_(0), nextEntityId_(0), player_(nullptr) {}

void FlatCraft::start() {
    ticks_=0;
    scheduler_.runTaskTimer([&](){
        ticks_++;
    },0,0);
    scheduler_.start();
}

void FlatCraft::stop() {
    scheduler_.stop();
}

void FlatCraft::createWorld(const std::string &name) {
    Random random;
    worlds_.emplace(name, std::make_unique<World>(name,random.nextLongLong()));
}

FlatCraft *FlatCraft::getInstance() {
    if(instance==nullptr){
        instance = std::make_unique<FlatCraft>();
    }
    return instance.get();
}

std::unique_ptr<FlatCraft> FlatCraft::instance = nullptr;

World *FlatCraft::getWorld(const std::string &name) const {
    auto it = worlds_.find(name);
    if(it==worlds_.end()) return nullptr;
    return it->second.get();
}

Player *FlatCraft::getPlayer() {
    return player_;
}

Scheduler *FlatCraft::getScheduler() {
    return &scheduler_;
}

EventManager *FlatCraft::getEventManager() {
    return &eventManager_;
}

void FlatCraft::loadSave(const std::string &name) {
    if(!existsSave(name)) return;
    save_ = name;
    loadWorlds();
    loadPlayer();
    loadEntities();
}

void FlatCraft::loadPlayer() {
    std::cout<<"loading player..."<<std::endl;
    std::ifstream in(save_+"/player.dat");
    if(in.is_open()){
        std::string s((std::istreambuf_iterator<char> (in)), (std::istreambuf_iterator<char> ()));
        in.close();
        if(!s.empty()){
            player_ = dynamic_cast<Player *>(registerEntity(Entity::deserialize(nlohmann::json::parse(s))));
            return;
        }
    }
    std::cout<<"failed"<<std::endl;
}

void FlatCraft::savePlayer() {
    std::cout<<"saving player..."<<std::endl;
    std::ofstream out(save_+"/player.dat");
    if(out.is_open()){
        out<<player_->serialize()->dump();
        out.close();
        return;
    }
    std::cout<<"failed"<<std::endl;
}

void FlatCraft::loadEntities() {
    std::cout<<"loading entities..."<<std::endl;
    std::ifstream in(save_+"/entities.dat");
    if(in.is_open()){
        std::string s((std::istreambuf_iterator<char> (in)), (std::istreambuf_iterator<char> ()));
        in.close();
        if(!s.empty()){
            auto json = nlohmann::json::parse(s);
            int amount = json.at("amount").get<int>();
            for (int i = 0; i < amount; ++i) {
                registerEntity(Entity::deserialize(json.at(std::to_string(i))));
            }
            return;
        }
    }
    std::cout<<"failed"<<std::endl;
}

void FlatCraft::saveEntities() {
    std::cout<<"saving entities..."<<std::endl;
    std::ofstream out(save_+"/entities.dat");
    if(out.is_open()){
        nlohmann::json json({{"amount",entities_.size()-1}});
        int i=0;
        for (const auto &item: entities_){
            if(item.first==player_->getId()) continue;
            json.emplace(std::to_string(i),*item.second->serialize());
            i++;
        }
        out<<json.dump();
        out.close();
        return;
    }
    std::cout<<"failed"<<std::endl;
}

void FlatCraft::loadWorld(const std::string &name) {
    std::ifstream in(save_+"/world/"+name+".dat");
    std::cout<<"found world save "<<name<<std::endl;
    if(in.is_open()){
        std::cout<<"loading world "<<name<<"..."<<std::endl;
        std::string s((std::istreambuf_iterator<char> (in)), (std::istreambuf_iterator<char> ()));
        in.close();
        if(!s.empty()){
            auto world = World::deserialize(nlohmann::json::parse(s));
            worlds_.emplace(name,std::move(world));
            std::cout<<"done"<<std::endl;
            return;
        }
        std::cout<<"failed"<<std::endl;
    }
    createWorld(name);
}

void FlatCraft::loadWorlds() {
    for(const auto& it : std::filesystem::directory_iterator(save_+"/world")){
        auto name = it.path().filename();
        if(name.extension()==".dat"){
            auto str = name.u8string();
            str = str.substr(0,str.length()-4);
            loadWorld(str);
        }
    }
}

void FlatCraft::saveWorld(const std::string &name) {
    World* world = getWorld(name);
    if(world!= nullptr){
        std::cout<<"saving world "<<name<<"..."<<std::endl;
        std::ofstream out(save_+"/world/"+name+".dat");
        out<<world->serialize()->dump();
        out.close();
        std::cout<<"done"<<std::endl;
    }
}

void FlatCraft::saveWorlds() {
    for (const auto &item: worlds_){
        saveWorld(item.first);
    }
}

void FlatCraft::save() {
    std::filesystem::create_directories(save_);
    std::filesystem::create_directories(save_+"/world");
    savePlayer();
    saveEntities();
    saveWorlds();
}

bool FlatCraft::existsSave(const std::string &name) const {
    return std::filesystem::exists(name);
}

void FlatCraft::createSave(const std::string &name) {
    save_=name;
    std::filesystem::create_directories(save_);
    std::filesystem::create_directories(save_+"/world");
    createWorld("main_world");
    auto world = getWorld("main_world");

    for(int i=255;i>=0;i--){
        if(MaterialHelper::isOccluded(world->getBlock(-1,i,true)->getMaterial()) ||
        MaterialHelper::isOccluded(world->getBlock(0,i,true)->getMaterial())){
            player_ = createEntity<Player>();
            player_->teleport(Location(*world,0,i+1));
            break;
        }
    }
}

Entity *FlatCraft::getEntity(int id) {
    auto it = entities_.find(id);
    if(it==entities_.end()) return nullptr;
    return it->second.get();
}

void FlatCraft::destroyEntity(Entity *entity) {
    auto world = entity->getWorld();
    if(world!=nullptr) entity->teleport(Location::INVALID_LOCATION);
    entities_.erase(entity->getId());
}

void FlatCraft::init() {
    Item::registerAllItems();
    EventType::init();
}

