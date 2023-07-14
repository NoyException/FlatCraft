//
// Created by Noy on 2023/7/14.
//

#include "app/Console.h"
#include "window/graph.h"

void Console::run() {
    running_ = true;
    std::chrono::milliseconds timeout(10);
    std::string input;
    while(running_){
        std::future<std::string> future = std::async(readString);
        if (future.wait_for(timeout) == std::future_status::ready)
            input = future.get();
        else continue;
        if(input=="stop"){
            running_ = false;
            graphFinish = false;
        }
    }
}

void Console::stop() {
    running_ = false;
}

std::string Console::readString() {
    std::string s;
    std::cin >> s;
    return s;
}
