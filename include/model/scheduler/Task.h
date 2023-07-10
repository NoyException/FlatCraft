//
// Created by Noy on 2023/7/4.
//

#ifndef FLATCRAFT_TASK_H
#define FLATCRAFT_TASK_H

#include "common.h"

class Task {
public:
    static constexpr int INFINITY_TIMES = -0x3f3f3f3f;
    Task(const std::function<void()>& task, int delay, int interval, int timesLeft);
    [[nodiscard]] bool isExpired() const;
    void cancel();
    void run();
private:
    std::function<void()> task_;
    int delay_;
    int interval_;
    int timesLeft_;
    int ticksLeft_;
};

#endif //FLATCRAFT_TASK_H
