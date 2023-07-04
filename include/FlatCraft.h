//
// Created by Noy on 2023/7/4.
//

#ifndef FLATCRAFT_FLATCRAFT_H
#define FLATCRAFT_FLATCRAFT_H

#include "common.h"
#include "world/World.h"

class FlatCraft {
public:
    void start();
    void createWorld(const std::string& name);
    [[nodiscard]] World* getWorld(const std::string& name) const;
    static FlatCraft* getInstance();
private:
    //name->World
    std::map<std::string,std::unique_ptr<World>> worlds_;
    static std::unique_ptr<FlatCraft> instance;
};

#endif //FLATCRAFT_FLATCRAFT_H
