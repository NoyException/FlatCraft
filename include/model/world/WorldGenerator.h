
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
    void generateMaterial(double start,int width,int octaves, double persistence,
                          double frequency,double amplitude ,int minY,Material,World& world,long long seed,long long treeSeed);
    void generateTree(double start,int width,int treeSeed,World& world,double *noise);
    bool haveTree(double x,int treeSeed);
    int* generateHash(int seed);
    void buildTree(int x,int y,World& world);
    void buildLeaves(int x,int y,World& world);
    void buildLog(int x,int y,World& world);
    void generateMineral(double start,int width,double amplitude ,int minY,Material,World& world,int times,long long seed);
    void generateCave(double startX,double startY,int width,int height,int octaves, double persistence,
                      double frequency,double amplitude ,int minY,World& world,long long seed);
    double grad(double x,double y,int hash);
    double noise(double x,double y,int *hash);
    double perlin(int *hash,double x, double y, int octaves, double persistence,double amplitude,double frequency,int minY);
};


#endif //FLATCRAFT_WORLDGENERATOR_H
