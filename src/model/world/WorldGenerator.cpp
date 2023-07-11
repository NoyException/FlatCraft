//
// Created by 30445 on 2023/7/9.
//

#include "model/world/WorldGenerator.h"
#include "common.h"
#include <algorithm>
#include <random>


int *WorldGenerator::generateHash(int seed) {
    srand(seed);
    int *hash = new int[256];
    for(int j=0;j<256;j++){
        int random = rand();
        random = random % 256;
        hash[j]=random;
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
    std::cout<<std::endl;
}


void WorldGenerator::generateMaterial(double start,int width,int octaves, double persistence, double frequency,double amplitude,int minY,
                                      Material a,World& world){
    int *hash=generateHash(1);
    auto *noiseArray = new double[width];
    for(int i=0;i<width;i++) {
        double x = (double) i / 32.0;
        noiseArray[i] = perlin(hash,x, octaves, persistence, amplitude, frequency, minY);
    }
    for(int i=0;i<=width;i++){
        for(int j=0;j<noiseArray[i];j++){
            world.setBlock(start+i,j, true,a);
            world.setBlock(start+i,j, false,a);
        }
    }
    if(a==Material::STONE){
        double newNoiseArray[width];
        for(int i=0;i<=width;i++){
            if(noiseArray[i]+1>62){
                world.setBlock(start+i,noiseArray[i]+1, true,Material::GRASS);
                world.setBlock(start+i,noiseArray[i]+1, false,Material::GRASS);
            }else{
                world.setBlock(start+i,noiseArray[i]+1, true,Material::DIRT);
                world.setBlock(start+i,noiseArray[i]+1, false,Material::DIRT);
            }

            double x = (double) i / ((double) width);
            newNoiseArray[i] = perlin(hash,x, octaves, persistence, 0.5, frequency, 5);
            for(int j=0;j<newNoiseArray[i];j++){
                world.setBlock(start+i,noiseArray[i]-j, true,Material::DIRT);
                world.setBlock(start+i,noiseArray[i]-j, false,Material::DIRT);
            }
        }
    }
    generateTree(start,width,2,world,noiseArray);
    delete[] noiseArray;
}

void WorldGenerator::generateTree(double start,int width,int treeSeed,World& world,double *noise) {
    int treeAddress=start;
    for(int i=0;i<=width;i++){
        double x = (double) i / 32.0;
        if(haveTree(x,noise,treeSeed)&& (start+i> treeAddress + 5) && (noise[i]>63)){
            treeAddress=start+i;
            for(int j=noise[i]+2;j<noise[i]+12;j++){
                //world.setBlock(start+i,j, true,Material::LOG);
                if(j>noise[i]+7){
                    for(int m=treeAddress-1;m<treeAddress+2;m++){
                        world.setBlock(m,j, true,Material::LEAVES);
                    }
                }
                if(j<noise[i]+10){
                    world.setBlock(start+i,j, false,Material::LOG);
                }
            }
        }
    }
}

bool WorldGenerator::haveTree(double x,double *noise,int treeSeed) {
    int *hash = generateHash(treeSeed);
    double addr = perlin(hash, x, 4, 0.5, 1, 1.0, 0);
    if (addr > 0.8) {
        return true;
    }
    return false;
}


