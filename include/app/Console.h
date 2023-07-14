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
    [[nodiscard]] bool isRunning() const;
private:
    bool running_ = false;
};


#endif //FLATCRAFT_CONSOLE_H
