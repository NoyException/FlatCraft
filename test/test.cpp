#include "common.h"
int main(){
    BoundingBox aabb(1,1,2,2);
    auto res = aabb.rayTrace({0,0.25},{1,1},10,1000);
    if(res.has_value()) std::cout<<res.value();
}