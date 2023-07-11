//
// Created by Noy on 2023/7/11.
//

#ifndef FLATCRAFT_RANDOM_H
#define FLATCRAFT_RANDOM_H

#include <random>

class Random {
public:
    Random();
    explicit Random(int seed);
    double nextDouble();
private:
    std::mt19937 gen_;
    std::uniform_real_distribution<> dis_;
};


#endif //FLATCRAFT_RANDOM_H
