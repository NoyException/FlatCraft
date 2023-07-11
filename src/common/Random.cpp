//
// Created by Noy on 2023/7/11.
//

#include "Random.h"

Random::Random() : gen_(std::random_device()()), dis_(0.0,1.0) {}

Random::Random(int seed) : gen_(seed), dis_(0.0,1.0) {}

double Random::nextDouble() {
    return dis_(gen_);
}
