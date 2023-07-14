//
// Created by Noy on 2023/7/14.
//

#include "app/Console.h"
#include "common.h"
#include "window/graph.h"

void Console::run() {
    running_ = true;
//    while(running_){
//        std::string input;
//        std::cin>>input;
//        if(input=="stop"){
//            running_ = false;
//            graphFinish = false;
//        }
//    }
}

void Console::stop() {
    running_ = false;
}
