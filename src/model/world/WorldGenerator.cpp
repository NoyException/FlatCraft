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
    Random random(world.getSeed());
    auto seed1=random.nextLongLong();
    auto seed2=random.nextLongLong();
    auto seed3=random.nextLongLong();
    auto seed4=random.nextLongLong();
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
    generateMaterial(-128,256,4,0.5,1.0,4,66,Material::STONE,world,seed1,seed2);//world.chunk
    generateMineral(-128,256,1.2,24,Material::LOG,world,5,seed3);
    generateCave(-128,1,256,60,6,0.5,1.0,1.0,0,world,seed4);
}
void WorldGenerator::generateMaterial(double start,int width,int octaves, double persistence, double frequency,double amplitude,int minY,Material a,World& world,long long seed,long long treeSeed){
    int *hash=generateHash(seed);
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
        generateTree(start,width,treeSeed,world,noiseArray);
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
        if(haveTree(x,treeSeed)&& (start+i> treeAddress + 5) && (noise[i]>63)){
            treeAddress=startX+i;
            buildTree(treeAddress,noise[i]+1,world);
        }
    }
}
bool WorldGenerator::haveTree(double x,int treeSeed) {
    int *hash = generateHash(treeSeed);
    double addr = perlin(hash, x, 4, 0.5, 1, 1.0, 0);
    delete []hash;
    return addr > 0.8;
}
void WorldGenerator::buildTree(int x, int y,World& world) {
    if(world.getBlock(x,y, true)->getMaterial()!=Material::AIR){
        buildLeaves(x,y,world);
        buildLog(x,y,world);
    }
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
void WorldGenerator::generateMineral(double start, int width,double amplitude, int minY, Material a, World &world,int times,long long seed) {

    Random rnd(seed);
    double mineralNoiseArrayX[300];
    double mineralNoiseArrayY[300];
    double prob;
    int z=1;
    int zz=-1;
    for(int tim=0;tim<times;tim++) {
        for (int i = 0; i < width; i++) {
            double xx = (double) i / 16.0;
            for (int j = 0; j < 20; j++) {
                double x = (double) j / 0.67;
                int *hash = generateHash(tim+ i+ j + seed);
                mineralNoiseArrayX[i] = perlin(hash, xx, 4, 0.5, amplitude, 1.0, 0);
                mineralNoiseArrayY[j] = perlin(hash, x, 4, 0.5, amplitude, 1.0, 0);
                if(j<5) {
                    prob=mineralNoiseArrayX[i]*mineralNoiseArrayY[j]*1.2;
                }else {
                    prob=mineralNoiseArrayX[i]*mineralNoiseArrayY[j];
                }
                double r=rnd.nextDouble();
                if(r*prob>8.8) {
                    int sizeX=rnd.nextInt(4);
                    int xm=i+start-1;
                    if(sizeX==0){
                        zz=-1*zz;
                    }else if(sizeX==1){
                        world.setBlock(xm,j+minY, true,Material::LOG);
                        world.setBlock(xm,j+minY+z, true,Material::LOG);
                        world.setBlock(xm+z,j+minY, true,Material::LOG);
                        z=-z;
                    } else if(sizeX==2){
                        world.setBlock(xm,j+minY, true,Material::LOG);
                        world.setBlock(xm+1,j+minY, true,Material::LOG);
                        world.setBlock(xm-1,j+minY, true,Material::LOG);
                        world.setBlock(xm,j+minY-1, true,Material::LOG);
                        world.setBlock(xm,j+minY+1, true,Material::LOG);
                        world.setBlock(xm+z,j+minY+zz, true,Material::LOG);
                        zz=-1*zz;
                        z=-1*z;
                    }else if(sizeX==3){
                        world.setBlock(xm,j+minY, true,Material::LOG);
                        world.setBlock(xm+1,j+minY, true,Material::LOG);
                        world.setBlock(xm-1,j+minY, true,Material::LOG);
                        world.setBlock(xm,j+minY-1, true,Material::LOG);
                        world.setBlock(xm,j+minY+1, true,Material::LOG);
                        world.setBlock(xm+1,j+minY+1, true,Material::LOG);
                        world.setBlock(xm+1,j+minY-1, true,Material::LOG);
                        world.setBlock(xm-1,j+minY+1, true,Material::LOG);
                        world.setBlock(xm-1,j+minY-1, true,Material::LOG);
                        world.setBlock(xm+1,j+minY+1, true,Material::LOG);
                        world.setBlock(xm+2,j+minY, true,Material::LOG);
                        world.setBlock(xm-2,j+minY, true,Material::LOG);
                        world.setBlock(xm+2*zz*z,j+minY, true,Material::STONE);
                        z=-1*z;
                    }
                }
            }
        }
    }
}

double WorldGenerator::grad(double x, double y, int hash) {
    int h = hash & 7;
    double u = h < 4 ? x : y;
    double v = h < 4 ? y : x;
    return ((h & 1) ? -u : u) + ((h & 2) ? -2.0 * v : 2.0 * v);
}

double WorldGenerator::noise(double x, double y, int *hash) {
    int X = (int)std::floor(x)&255;
    int Y = (int)std::floor(y)&127;
    x -= std::floor(x);
    y -= std::floor(y);
    double u = x * x * x * (x * (x * 6 -15) +10);
    double v = y * y * y * (y * (y * 6 - 15) + 10);
    int A = hash[X] + Y;
    int B = hash[X + 1] + Y;
    int C = hash[X] + Y+ 1;
    int D = hash[X + 1] + Y + 1;

    double g1 = grad( x, y,hash[A]);
    double g2 = grad( x -1, y,hash[B]);
    double g3 = grad(x, y -1,hash[C]);
    double g4 = grad( x -1, y -1,hash[D]);

    return lerp(lerp(g1, g2, u), lerp(g3, g4, u), v);
}

double WorldGenerator::perlin(int *hash,double x, double y, int octaves, double persistence,double amplitude,double frequency,int minY) {
    double total =0.0;
    // 循环累加每个频率的噪声值
    for (int i=0; i<octaves; i++) {
        total += noise(x*frequency,y*frequency,hash)*amplitude;
        frequency *=2.0;
        amplitude *=persistence;
    }
    // 返回总噪声值
    return total+minY;
}

void WorldGenerator::generateCave(double startX, double startY, int width, int height, int octaves, double persistence,
                                  double frequency, double amplitude, int minY, World &world,
                                  long long seed ){
    int *hash=generateHash(seed);
    double noiseArray[256][128];
    for(int i=0;i<width;i++) {
        double x = (double) i / 32.0;
        for(int j=0;j<height;j++){
            double y=(double) j/8.0;
            noiseArray[i][j]=perlin(hash,x,y, octaves, persistence, amplitude, frequency, minY);
        }
    }

    int xStart = std::floor(startX);
    int yStart = std::floor(startY);
    for(int i=0;i<=width;i++){
        for(int j=0;j<=height;j++){
            if(noiseArray[i][j]<-0.3){
                if ( world.getBlock(xStart+i,yStart+j, true)->getMaterial()!=Material::WATER){
                    world.setBlock(xStart+i,yStart+j, true,Material::AIR);
                }
            }
        }
    }
}



