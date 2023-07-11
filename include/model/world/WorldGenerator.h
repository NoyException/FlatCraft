
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
    double noise(double x,int *hash);
    double perlin(int *hash,double x, int octaves, double persistence,double amplitude,double frequency,int minY);
    void generate(World& world);
    void generateMaterial(double start,int width,int octaves, double persistence,double frequency,double amplitude ,int minY,Material,World& world);
    void generateTree(double start,int width,int treeSeed,World& world,double *noise);
    bool haveTree(double x,double *noise,int treeSeed);
    int *generateHash(int seed);

private:;;
};


#endif //FLATCRAFT_WORLDGENERATOR_H
