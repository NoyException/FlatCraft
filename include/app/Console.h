//
// Created by Noy on 2023/7/14.
//

#ifndef FLATCRAFT_CONSOLE_H
#define FLATCRAFT_CONSOLE_H

#include "common.h"

class Console {
public:
    void run();
    void stop();
private:
    [[nodiscard]] static std::string readString() ;
    bool running_ = false;
};


#endif //FLATCRAFT_CONSOLE_H
