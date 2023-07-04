//
// Created by Noy on 2023/7/4.
//

#include "scheduler/Task.h"

Task::Task(const std::function<void()>& task, int delay, int interval, int timesLeft) :
        task_(task), delay_(delay), interval_(interval), timesLeft_(timesLeft) {
    ticksLeft_ = delay;
}

bool Task::isExpired() const{
    return timesLeft_<=0 && timesLeft_!=INFINITY_TIMES;
}

void Task::run() {
    if(ticksLeft_>0){
        ticksLeft_--;
        return;
    }
    if(timesLeft_>0) timesLeft_--;
    task_();
    ticksLeft_ = interval_;
}

void Task::cancel() {
    timesLeft_ = 0;
}
