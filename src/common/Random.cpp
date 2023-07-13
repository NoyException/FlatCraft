//
// Created by Noy on 2023/7/11.
//

#include "Random.h"
#include <chrono>

unsigned long long nanoSecond(){
    auto now = std::chrono::high_resolution_clock::now(); // 获取当前的时间点
    auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()); // 获取从某个固定的时间点到现在的纳秒数
    return nanoseconds.count();
}

Random::Random() : Random(nanoSecond()) {}

Random::Random(unsigned long long seed) : seed_(seed) {}

unsigned int Random::next(int bits) {
    seed_ = (seed_ * MULTIPLIER + ADDEND) & MASK;
    return (unsigned int)(seed_ >> (48 - bits));
}

unsigned int Random::nextInt() {
    return next(32);
}

unsigned int Random::nextInt(unsigned int bound) {
    if(bound == 0) return 0;
    unsigned int r = next(31);
    unsigned int m = bound - 1;
    if ((bound & m) == 0)  // i.e., bound is a power of 2
        r = (unsigned int)((bound * (unsigned long long)r) >> 31);
    else { // reject over-represented candidates
        for (unsigned int u = r;
             u - (r = u % bound) + m < 0;
             u = next(31));
    }
    return r;
}

unsigned long long Random::nextLongLong() {
    return ((unsigned long long)(next(32)) << 32) + next(32);
}

bool Random::nextBool() {
    return next(1) != 0;
}

float Random::nextFloat() {
    return (float)next(24) / ((float)(1 << 24));
}

double Random::nextDouble() {
    return (double)(((unsigned long long)(next(26)) << 27) + next(27)) * DOUBLE_UNIT;
}

unsigned long long Random::getCurrentSeed() const {
    return seed_;
}

