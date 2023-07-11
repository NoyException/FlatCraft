
//
// Created by 30445 on 2023/7/9.
//

#ifndef FLATCRAFT_WORLDGENERATOR_H
#define FLATCRAFT_WORLDGENERATOR_H

#include "model/world/World.h"

class WorldGenerator {
public:
    static double lerp(double a, double b, double t);
    static double grad(int hash, double x);
    double noise(double x);
    double perlin(double x, int octaves, double persistence,double amplitude,double frequency,int minY);
    void generate(World& world);
    void getHash(int x);
    void generateMaterial(double start,int width,int octaves, double persistence,double frequency,double amplitude ,int minY,Material,World& world);
private:
    int Hash[256];
    int seed=10;
};


#endif //FLATCRAFT_WORLDGENERATOR_H
