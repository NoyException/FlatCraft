#include "common.h"
int main(){
//    std::cout<<(int)0.5<<" "<<(int)-0.5;
//    return 0;
//    Random rand;
//    for (int i = 0; i < 10; ++i) {
//        double d = rand.nextDouble();
//        std::cout<<d<<std::endl;
//    }
    BoundingBox aabb(-32,65,-31,66);
    Vec2d v(-0.9787321,0.2051422);
    auto res = aabb.rayTrace({-28.214,66.9},v,6,0,0);
    if(res.has_value()) std::cout<<res->hitPoint;
}