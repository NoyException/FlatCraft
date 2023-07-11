//
// Created by Noy on 2023/7/6.
//

#include <list>
#include <iostream>
#include <fstream>
#include "Material.h"

MaterialInfo MaterialInfo::deserialize(const std::string& name, const nlohmann::json &json) {
    int id = json.at("id").get<int>();
    int maxStacks = json.at("max_stacks").get<int>();
    double hardness = json.at("hardness").get<double>();
    double antiExplosion = json.at("anti_explosion").get<double>();
    MaterialInfo info(id, maxStacks, hardness, antiExplosion);
    std::list<std::string> flags = json.at("flags");
    for (const auto &item: flags){
        if(item=="OCCLUDED") info.flags_.insert(MaterialFlag::OCCLUDED);
        else if(item=="SOLID") info.flags_.insert(MaterialFlag::SOLID);
        else if(item=="LIQUID") info.flags_.insert(MaterialFlag::LIQUID);
        else if(item=="AIR") info.flags_.insert(MaterialFlag::AIR);
    }
    std::list<std::string> tools = json.at("tools");
    for (const auto &item: tools){
        info.tools_.insert(item);
    }
    info.name_ = name;
    return info;
}

MaterialInfo::MaterialInfo(int id, int maxStacks, double hardness, double antiExplosion) :
id_(id),maxStacks_(maxStacks),hardness_(hardness),antiExplosion_(antiExplosion) {}


void MaterialHelper::registerMaterial(const std::string& name){
    std::ifstream in("../resources/material/"+name+".json");
    if(in.is_open()){
        std::cout<<"register material "<<name<<"."<<std::endl;
        std::string s((std::istreambuf_iterator<char> (in)), (std::istreambuf_iterator<char> ()));
        in.close();
        if(!s.empty()){
            MaterialInfo info = MaterialInfo::deserialize(name, nlohmann::json::parse(s));
            byId.emplace(info.id_,std::move(info));
        }
    }
}

void MaterialHelper::registerAllMaterials(){
    registerMaterial("air");
    registerMaterial("stone");
    registerMaterial("dirt");
    registerMaterial("grass");
    registerMaterial("water");
    registerMaterial("bedrock");
    registerMaterial("log");
    registerMaterial("leaves");
}

MaterialInfo *MaterialHelper::getInfo(Material material) {
    auto it = byId.find(static_cast<int>(material));
    if(it == byId.end()) return nullptr;
    return &it->second;
}

std::string MaterialHelper::getName(Material material) {
    return getInfo(material)->name_;
}

bool MaterialHelper::containsFlag(Material material, MaterialFlag flag) {
    return getInfo(material)->flags_.count(flag);
}

bool MaterialHelper::isOccluded(Material material){
    return containsFlag(material,MaterialFlag::OCCLUDED);
//        switch (material) {
//            case Material::GRASS:
//            case Material::DIRT:
//            case Material::STONE:
//            case Material::BED_ROCK:
//                return true;
//            default:
//                return false;
//        }
}

bool MaterialHelper::isSolid(Material material){
    return containsFlag(material,MaterialFlag::SOLID);
//        switch (material) {
//            case Material::GRASS:
//            case Material::DIRT:
//            case Material::STONE:
//            case Material::BED_ROCK:
//                return true;
//            default:
//                return false;
//        }
}

bool MaterialHelper::isAir(Material material){
    return containsFlag(material,MaterialFlag::AIR);
//        switch (material) {
//            case Material::AIR:
//                return true;
//            default:
//                return false;
//        }
}

bool MaterialHelper::isLiquid(Material material){
    return containsFlag(material,MaterialFlag::LIQUID);
//        switch (material) {
//            case Material::WATER:
//                return true;
//            default:
//                return false;
//        }
}

double MaterialHelper::getHardness(Material material){
    return getInfo(material)->hardness_;
}

std::unordered_map<int,MaterialInfo> MaterialHelper::byId;
