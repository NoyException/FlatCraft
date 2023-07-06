//
// Created by Noy on 2023/7/4.
//

#ifndef FLATCRAFT_SCHEDULER_H
#define FLATCRAFT_SCHEDULER_H

#include "common.h"
#include <chrono>
#include <thread>
#include <mutex>

#include "scheduler/Task.h"

using RawTask = std::function<void()>;

class Scheduler {
public:
    Scheduler();
    void start();
    void stop();
    void runTask(const RawTask& task);
    void runTaskLater(const RawTask& task, int delay);
    void runTaskTimer(const RawTask& task, int delay, int interval);
    void runTaskFiniteTimer(const RawTask& task, int delay, int interval, int times);
private:
    void run();
    bool running_;
    std::mutex mtx_;
    std::list<Task> tasks_;
    std::unique_ptr<std::thread> thread_;
    decltype(std::chrono::high_resolution_clock::now()) timestamp_;
};

#endif //FLATCRAFT_SCHEDULER_H
