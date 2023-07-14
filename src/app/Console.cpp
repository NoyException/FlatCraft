//
// Created by Noy on 2023/7/14.
//

#include "app/Console.h"
#include "window/graph.h"

void Console::run() {
    running_ = true;
    std::string input;
//    while(running_){
//        std::getline(std::cin,input);
//        if(input=="#") break;
//        if(input=="stop"){
//            running_ = false;
//            graphFinish = false;
//            break;
//        }
//        else if(!input.empty()){
//            std::cout<<"unknown command"<<std::endl;
//        }
//    }
}

void Console::stop() {
    running_ = false;
    std::cin.putback('#');
    std::cin.putback('\n');
}

bool Console::isRunning() const {
    return running_;
}
