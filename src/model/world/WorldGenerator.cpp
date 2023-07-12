//
// Created by 30445 on 2023/7/9.
//

#include "model/world/WorldGenerator.h"
#include "common.h"
#include <algorithm>


int *WorldGenerator::generateHash(int seed) {
    Random rnd(seed);
    int *hash = new int[256];
    for(int j=0;j<256;j++){
        hash[j]=(int) rnd.nextInt(256);
    }
    return hash;
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

double WorldGenerator::noise(double x,int *hash) {
    int X = (int)std::floor(x)&255;
    x -= std::floor(x);
    double u = x * x * x * (x * (x * 6 -15) +10);
    int A = hash[X];
    int B = hash[X + 1];
    double g1 = grad(hash[A], x);
    double g2 = grad(hash[B], x -1);
    return lerp(g1, g2, u);
}

//倍频octaves可以增加图形的变化程度（persistence影响平滑程度，建议保持0.5不变）
//振幅amplitude最低与最高的值
//frequency越大，噪声值变化越快，建议保持1.0不变
double WorldGenerator::perlin(int *hash,double x, int octaves, double persistence,double amplitude ,double frequency,int minY) {
    double total = 0.0;
    for (int i = 0; i < octaves; i++) {
        total += noise(x * frequency,hash) * amplitude;
        frequency *= 2.0;
        amplitude *= persistence;
    }
    return total+minY;
}

void WorldGenerator::generate(World &world) {
    for(int i=0;i<256;i++){
        for(int j=-128;j<=128;j++){
            world.setBlock(j,i, true,Material::AIR);
            world.setBlock(j,i, false,Material::AIR);
        }
    }
    for(int i=48;i<63;i++){
        for(int j=-128;j<=128;j++){
            world.setBlock(j,i, true,Material::WATER);
            world.setBlock(j,i, false,Material::DIRT);
            if(i==62){
                world.setBlock(j,i, false,Material::GRASS);
            }
        }
    }
    generateMaterial(-128,256,4,0.5,1.0,4,66,Material::STONE,world);//world.chunk
}


void WorldGenerator::generateMaterial(double start,int width,int octaves, double persistence, double frequency,double amplitude,int minY,
                                      Material a,World& world){
    int *hash=generateHash(world.seed_);
    auto *noiseArray = new double[width];
    for(int i=0;i<width;i++) {
        double x = (double) i / 32.0;
        noiseArray[i] = perlin(hash,x, octaves, persistence, amplitude, frequency, minY);
    }
    int startX = std::floor(start);
    for(int i=0;i<=width;i++){
        for(int j=0;j<noiseArray[i];j++){
            world.setBlock(startX+i,j, true,a);
            world.setBlock(startX+i,j, false,a);
        }
    }
    if(a==Material::STONE){
        //double* newNoiseArray = new double[width];
        double newNoiseArray[300];
        generateTree(start,width,2,world,noiseArray);
        for(int i=0;i<=width;i++){
            int noise = std::floor(noiseArray[i]);
            if(noise+1>61){
                world.setBlock(startX+i,noise+1, true,Material::GRASS);
                world.setBlock(startX+i,noise+1, false,Material::GRASS);
            }else{
                world.setBlock(startX+i,noise+1, true,Material::DIRT);
                world.setBlock(startX+i,noise+1, false,Material::DIRT);
            }

            double x = (double) i / ((double) width);
            newNoiseArray[i] = perlin(hash,x, octaves, persistence, 0.5, frequency, 5);
            for(int j=0;j<newNoiseArray[i];j++){
                world.setBlock(startX+i,noise-j, true,Material::DIRT);
                world.setBlock(startX+i,noise-j, false,Material::DIRT);
            }
        }
        //delete[] newNoiseArray;
    }

    delete[] noiseArray;
    delete[] hash;
}

void WorldGenerator::generateTree(double start,int width,int treeSeed,World& world,double *noise) {
    int startX = std::floor(start);
    int treeAddress=startX;
    for(int i=0;i<=width;i++){
        double x = (double) i / 32.0;
        if(haveTree(x,noise,treeSeed)&& (start+i> treeAddress + 5) && (noise[i]>63)){
            treeAddress=startX+i;
            buildTree(treeAddress,noise[i]+1,world);
        }
    }
}

bool WorldGenerator::haveTree(double x,double *noise,int treeSeed) {
    int *hash = generateHash(treeSeed);
    double addr = perlin(hash, x, 4, 0.5, 1, 1.0, 0);
    delete []hash;
    return addr > 0.8;
}

void WorldGenerator::buildTree(int x, int y,World& world) {
    buildLeaves(x,y,world);
    buildLog(x,y,world);
}

void WorldGenerator::buildLeaves(int x, int y,World& world) {
    int leaveWidth=2;
    for(int i=y+4;i<y+8;i++){
        if(i==y+6){
            leaveWidth-=1;
        }
        for(int j=x-leaveWidth;j<x+leaveWidth+1;j++){
            world.setBlock(j,i, false,Material::LEAVES);
        }
        for(int j=x-(leaveWidth-1);j<x+(leaveWidth-1)+1;j++){
            world.setBlock(j,i, true,Material::LEAVES);
        }
    }
    world.setBlock(x,y+7, true,Material::AIR);
}

void WorldGenerator::buildLog(int x, int y,World& world) {
    for(int i=y;i<y+7;i++){
        world.setBlock(x,i, false,Material::LOG);
    }
}
/*
void WorldGenerator::generateMineral(double start, int width, int octaves, double persistence, double frequency,
                                     double amplitude, int minY, Material, World &world,int hashSeed,int times) {
    int *hash = generateHash(hashSeed);
    double mineralNoiseArray[300];
    for(int i=0;i<width;i++){
        double x=(double) i/16.0;
        mineralNoiseArray[i]= perlin(hash, x, 4, 0.5, amplitude, 1.0, 0);
    }
    for(int i=0;i<width;i++){
        for(int j=minY-mineralNoiseArray[i];j<minY+mineralNoiseArray[i]+1;j++){
            for(int z=0;z<times;z++){
                if(haveMineral(i,))
            }
        }
    }
}

bool WorldGenerator::haveMineral(double x,double *noise,int mineralSeed) {
    int *hash = generateHash(mineralSeed);
    double addr = perlin(hash, x, 4, 0.5, 1, 1.0, 0);
    delete []hash;
    return addr > 0.8;
}*/

