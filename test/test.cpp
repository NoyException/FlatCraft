#include "common.h"
int main(){
//    std::cout<<(int)0.5<<" "<<(int)-0.5;
//    return 0;
    BoundingBox aabb(1,63,2,64);
    Vec2d v(0.2,0);
    auto res = aabb.rayTrace({0.44,64.9},v,v.length(),0.4,0.9);
    if(res.has_value()) std::cout<<res->hitPoint;
}