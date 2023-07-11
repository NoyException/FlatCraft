//
// Created by 30445 on 2023/7/9.
//

#include "model/world/WorldGenerator.h"
#include "common.h"
#include <algorithm>
#include <random>

void WorldGenerator::getHash(int seed) {
    srand(seed);
    for(int j=0;j<256;j++){
        int random = rand();
        random = random % 256;
        Hash[j]=random;
    }
}

double WorldGenerator::grad(int hash, double x) {
    int h = hash & 15;
    double g = 1.0 + (h & 7);
    if (h & 8) g = -g;
    return g * x;
}

double WorldGenerator::lerp(double a, double b, double t) {
    return a + t * (b - a);
}

double WorldGenerator::noise(double x) {
    int X = (int)std::floor(x)&255;
    x -= std::floor(x);//+ hash(X,seed);
    double u = x * x * x * (x * (x * 6 -15) +10);
    int A = Hash[X];
    int B = Hash[X + 1];
    double g1 = grad(Hash[A], x);
    double g2 = grad(Hash[B], x -1);
    return lerp(g1, g2, u);
}

//倍频octaves可以增加图形的变化程度（persistence影响平滑程度，建议保持0.5不变）
//振幅amplitude最低与最高的值
//frequency越大，噪声值变化越快，建议保持1.0不变
double WorldGenerator::perlin(double x, int octaves, double persistence,double amplitude ,double frequency,int minY) {
    double total = 0.0;
    for (int i = 0; i < octaves; i++) {
        total += noise(x * frequency) * amplitude;
        frequency *= 2.0;
        amplitude *= persistence;
    }
    return total+minY;
}

void WorldGenerator::generate(World &world) {
    getHash(1);//(world.seed);
    for(int i=0;i<256;i++){
        for(int j=-128;j<=128;j++){
            world.setBlock(j,i, true,Material::AIR);
            world.setBlock(j,i, false,Material::AIR);
        }
    }
    for(int i=48;i<63;i++){
        for(int j=-128;j<=128;j++){
            world.setBlock(j,i, true,Material::WATER);
            world.setBlock(j,i, false,Material::WATER);
        }
    }
    generateMaterial(-128,256,4,0.5,1.0,4,66,Material::STONE,world);//world.chunk
    //generateMaterial(0,256,4,0.5,1.0,15,50,Material::STONE,world);//world.chunk
    std::cout<<std::endl;
}


void WorldGenerator::generateMaterial(double start,int width,int octaves, double persistence, double frequency,double amplitude,int minY,
                                      Material a,World& world){
    double* noiseArray = new double[width];
    for(int i=0;i<width;i++) {
        double x = (double) i / 32.0;
        noiseArray[i] = perlin(x, octaves, persistence, amplitude, frequency, minY);
    }
    for(int i=0;i<=width;i++){
        for(int j=0;j<noiseArray[i];j++){
            world.setBlock(start+i,j, true,a);
            world.setBlock(start+i,j, false,a);
        }
    }
    if(a==Material::STONE){
        double* newNoiseArray = new double[width];
        for(int i=0;i<=width;i++){
            world.setBlock(start+i,noiseArray[i]+1, true,Material::GRASS);
            world.setBlock(start+i,noiseArray[i]+1, false,Material::GRASS);
            double x = (double) i / ((double) width);
            newNoiseArray[i] = perlin(x, octaves, persistence, 0.5, frequency, 5);
            for(int j=0;j<newNoiseArray[i];j++){
                world.setBlock(start+i,noiseArray[i]-j, true,Material::DIRT);
                world.setBlock(start+i,noiseArray[i]-j, false,Material::DIRT);
            }
        }
        delete[] newNoiseArray;
    }

    delete[] noiseArray;
    
}