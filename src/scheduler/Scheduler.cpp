//
// Created by Noy on 2023/7/4.
//

#include "scheduler/Scheduler.h"

void preciseSleepUntil(decltype(std::chrono::high_resolution_clock::now()) to) {

    static long long estimate = 5e6;
    static long long mean = 5e6;
    static long long m2 = 0;
    static int64_t count = 1;

    long long seconds = (to-std::chrono::high_resolution_clock::now()).count();

    while (seconds > estimate) {
        auto start = std::chrono::high_resolution_clock::now();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        auto end = std::chrono::high_resolution_clock::now();

        long long observed = (end - start).count();
        seconds-=observed;

        ++count;
        long long delta = observed - mean;
        mean += delta / count;
        m2   += delta * (observed - mean);
        double stddev = sqrt((double)m2 / ((double)count - 1.0));
        estimate = mean + (long long)stddev;
    }

    // spin lock
//    int i=0;
    while (std::chrono::high_resolution_clock::now()<to);
//    std::cout<<"# "<<i<<std::endl;
}

Scheduler::Scheduler() : running_(false) {

}

void Scheduler::run(){
    std::lock_guard<std::mutex> lock(mtx_);

    tasks_.remove_if([](Task &task){return task.isExpired();});
    for (auto &task: tasks_){
        task.run();
    }
}

void Scheduler::start(){
    running_ = true;
    timestamp_ = std::chrono::high_resolution_clock::now();

    thread_ = std::make_unique<std::thread>([this]() {
        while (running_) {
            preciseSleepUntil(timestamp_);//std::this_thread::sleep_until(timestamp_);
            run();
            timestamp_+=std::chrono::milliseconds(50);
            auto tmp = std::chrono::high_resolution_clock::now()+std::chrono::milliseconds(50);
            if(timestamp_<tmp) timestamp_=tmp;
        }
    });

    thread_->detach();
}

void Scheduler::stop() {
    running_ = false;
    thread_->join();
}

void Scheduler::runTask(const RawTask& task) {
    runTaskFiniteTimer(task, 1, 0, 1);
}

void Scheduler::runTaskLater(const RawTask& task, int delay) {
    runTaskFiniteTimer(task, delay, 0, 1);
}

void Scheduler::runTaskTimer(const RawTask& task, int delay, int interval) {
    runTaskFiniteTimer(task, delay, interval, Task::INFINITY_TIMES);
}

void Scheduler::runTaskFiniteTimer(const RawTask &task, int delay, int interval, int times) {
    std::lock_guard<std::mutex> lock(mtx_);
    tasks_.emplace_back(task,delay,interval,times);
}