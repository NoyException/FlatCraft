#include "common.h"
int main(){
    BoundingBox aabb(-67,63,-66,64);
    Vec2d v(0,-0.28);
    auto res = aabb.rayTrace({-66.58,65.08},v,v.length(),0.4,0.9);
    if(res.has_value()) std::cout<<res->hitPoint;
}