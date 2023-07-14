//
// Created by Noy on 2023/7/11.
//

#ifndef FLATCRAFT_RANDOM_H
#define FLATCRAFT_RANDOM_H

class Random {
public:
    Random();
    explicit Random(unsigned long long seed);
protected:
    unsigned int next(int bits);
public:
    unsigned int nextInt();
    unsigned int nextInt(unsigned int bound);
    unsigned long long nextLongLong();
    bool nextBool();
    float nextFloat();
    double nextDouble();
    [[nodiscard]] unsigned long long getCurrentSeed() const;
private:
    static constexpr unsigned long long MULTIPLIER = 0x5DEECE66DLL;
    static constexpr unsigned long long ADDEND = 0xBLL;
    static constexpr unsigned long long MASK = (1LL << 48) - 1;
    static constexpr double DOUBLE_UNIT = 0x1.0p-53;
    unsigned long long seed_;
};


#endif //FLATCRAFT_RANDOM_H
