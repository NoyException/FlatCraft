//
// Created by Noy on 2023/7/4.
//

#ifndef FLATCRAFT_SCHEDULER_H
#define FLATCRAFT_SCHEDULER_H

#include "common.h"
#include <chrono>

#include "Task.h"

using RawTask = std::function<void()>;

class Scheduler {
public:
    Scheduler();
    void start();
    void stop();
    [[nodiscard]] bool isRunning() const;
    void sleep(long long ticks);
    std::shared_ptr<Task> runTask(const RawTask& task);
    std::shared_ptr<Task> runTaskLater(const RawTask& task, int delay);
    std::shared_ptr<Task> runTaskTimer(const RawTask& task, int delay, int interval);
    std::shared_ptr<Task> runTaskFiniteTimer(const RawTask& task, int delay, int interval, int times);
private:
    void run();
    long long sleep_;
    bool running_;
    std::mutex mtx_;
    std::list<std::shared_ptr<Task>> tasks_;
    std::unique_ptr<std::thread> thread_;
    decltype(std::chrono::high_resolution_clock::now()) timestamp_;
};

#endif //FLATCRAFT_SCHEDULER_H
