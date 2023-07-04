//
// Created by Noy on 2023/7/4.
//

#include "FlatCraft.h"

void FlatCraft::start() {

}

void FlatCraft::createWorld(const std::string &name) {
    worlds_.emplace(name, std::make_unique<World>(name));
}

FlatCraft *FlatCraft::getInstance() {
    return instance.get();
}

std::unique_ptr<FlatCraft> FlatCraft::instance = std::make_unique<FlatCraft>();

World *FlatCraft::getWorld(const std::string &name) const {
    return worlds_.find(name)->second.get();
}
