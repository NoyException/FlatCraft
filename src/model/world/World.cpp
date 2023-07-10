//
// Created by Noy on 2023/7/3.
//


#include <utility>

#include "model/world/World.h"
#include "model/FlatCraft.h"

World::World(const std::string& name) : name_(name), ticks_(0), weather_(Weather::CLEAR) {
    init();
}

nlohmann::json World::serialize() const {
    nlohmann::json json({
        {"name",name_},
        {"ticks",ticks_}
    });
    nlohmann::json blocks;
    for(int i=-128;i<=128;i++) {
        for (int j = 0; j < 256; j++) {
            for(int k = 0; k <= 1; k++){
                std::stringstream ss;
                ss<<i<<"_"<<j<<"_"<<k;
                blocks.emplace(ss.str(), getBlock(i,j,k)->serialize());
            }
        }
    }
    json.emplace("blocks",std::move(blocks));
    return std::move(json);
}

World World::deserialize(const nlohmann::json &json) {
    World world(json.at("name").get<std::string>());
    world.ticks_ = json.at("ticks").get<long long>();
    auto blocks = json.at("blocks");
    for(int i=-128;i<=128;i++) {
        for (int j = 0; j < 256; j++) {
            for(int k = 0; k <= 1; k++) {
                std::stringstream ss;
                ss << i << "_" << j << "_" << k;
                Block block = Block::deserialize(Location(world.name_, i, j),
                                                 k,blocks.at(ss.str()));
                int hash = (i << 11) ^ (j << 1) ^ k;
                world.blocks_[hash] = std::make_unique<Block>(block);
            }
        }
    }
    return std::move(world);
}

std::string World::getName() const {
    return name_;
}

Block* World::getBlock(int x, int y, bool front) const {
    auto it = blocks_.find((x<<11)^(y<<1)^front);
    if(it==blocks_.end()) return {};
    return it->second.get();
}

Block *World::getBlock(const Vec2d &v, bool front) const {
    return getBlock(v.getBlockX(),v.getBlockY(),front);
}

Block* World::getBlock(const Location &location, bool front) const {
    if(location.getRawWorld()!=name_) return nullptr;
    return getBlock(location.getBlockX(), location.getBlockY(), front);
}

void World::notifyTeleported(Entity &entity) {
    if(entity.getLocation().getRawWorld()==name_)
        entities_.insert(&entity);
    else
        entities_.erase(&entity);
}

void World::getEntities(std::vector<Entity*> &entities) const {
    for (const auto &item: entities_){
        entities.push_back(item);
    }
}

void World::getEntities(std::vector<Entity*> &entities, bool (*filter)(const Entity &)) const {
    for (const auto &item: entities_){
        if(filter(*item)) entities.push_back(item);
    }
}

void World::init() {
    for(int i=-128;i<=128;i++){
        for(int j=0;j<256;j++){
            int hash = (i<<11)^(j<<1);
            Material m;
            if(j==0) m = Material::BED_ROCK;
            else if(j<48) m = Material::STONE;
            else if(j<63) m = Material::DIRT;
            else if(j==63) m = Material::GRASS;
            else m = Material::AIR;
            if(m==Material::GRASS && i%2) m=Material::STONE;
            blocks_[hash] = std::make_unique<Block>(m,Location(name_,i,j),false);
            blocks_[hash^1] = std::make_unique<Block>(m,Location(name_,i,j),true);
        }
    }
    setBlock(5,64, true,Material::DIRT);
}

bool isCloseToRay(const Vec2d& point, const Vec2d& startPoint, const Vec2d& direction, double maxDistance, double epsilon) {
    // 如果direction是零向量，无法确定射线的方向，返回false
    if (direction.getX() == 0 && direction.getY() == 0) {
        return false;
    }
    // 计算点point到射线的垂足footPoint
    // 先将射线方向单位化
    Vec2d dir = direction;
    dir.normalize();
    // 然后计算点point到起点startPoint的向量
    Vec2d vec = point - startPoint;
    // 再计算点point在射线方向上的投影长度
    double projLen = vec.getX() * dir.getX() + vec.getY() * dir.getY();
    // 最后计算垂足footPoint的坐标
    Vec2d footPoint(startPoint.getX() + projLen * dir.getX(), startPoint.getY() + projLen * dir.getY());

    // 判断垂足footPoint是否在射线上，即投影长度projLen是否大于等于零且小于等于maxDistance
    if (projLen >= -epsilon && projLen <= maxDistance+epsilon) {
        // 计算点point到垂足footPoint的距离
        double dist = (point.getX() - footPoint.getX()) * (point.getX() - footPoint.getX()) + (point.getY() - footPoint.getY()) * (point.getY() - footPoint.getY());
        // 判断距离是否小于等于epsilon
        if (dist <= epsilon*epsilon) {
            return true;
        }
    }
    // 其他情况返回false
    return false;
}

std::unique_ptr<RayTraceResult> World::rayTrace(const Location &location, const Vec2d &direction,
                                                double maxDistance, double xSize, double ySize,
                                                const std::function<bool(Material)>& blockFilter,
                                                const std::function<bool(Entity *)>& entityFilter) const {
    if(direction.getX()==0 && direction.getY()==0) return nullptr;
    Vec2d dir = direction;
    dir.normalize();
    Vec2d startPoint = location.toVec2d();
    std::optional<Vec2d> closestPoint = std::nullopt;
    double minDistance = maxDistance*maxDistance+1;
    Entity* hitEntity = nullptr;
    Block* hitBlock = nullptr;
    BoundingBox::Face hitFace = BoundingBox::Face::BOTTOM;
    //与实体碰撞
    for (auto &item: entities_){
        if(entityFilter(item)){
            auto res = item->getBoundingBox().rayTrace(startPoint, dir, maxDistance, xSize, ySize);
            if(res.has_value()){
                double len = (res->hitPoint-startPoint).lengthSquared();
                if(len < minDistance){
                    minDistance = len;
                    closestPoint = res->hitPoint;
                    hitEntity = item;
                    hitFace = res->hitFace;
                }
            }
        }
    }
    BoundingBox rayPoint(startPoint-Vec2d(xSize,ySize),startPoint+Vec2d(xSize,ySize));
    BoundingBox rayBegin = rayPoint;
    rayBegin.expand(1,1,1,1);
    BoundingBox rayEnd = rayBegin+dir*maxDistance;
    BoundingBox rayUnion = rayBegin+rayEnd;
//    std::list<std::pair<Vec2d,Vec2d>> edges;
//    //顺时针环
//    if(dir.getX()<0 && dir.getY()<0){
//        edges.emplace_back(Vec2d(rayBegin.getMinX(),rayBegin.getMaxY()),Vec2d(rayBegin.getMaxX(),rayBegin.getMinY()));
//        edges.emplace_back(Vec2d(rayBegin.getMaxX(),rayBegin.getMinY()),Vec2d(rayEnd.getMaxX(),rayEnd.getMinY()));
//        edges.emplace_back(Vec2d(rayEnd.getMaxX(),rayEnd.getMinY()),Vec2d(rayEnd.getMinX(),rayEnd.getMinY()));
//        edges.emplace_back(Vec2d(rayEnd.getMinX(),rayEnd.getMinY()),Vec2d(rayEnd.getMinX(),rayEnd.getMaxY()));
//        edges.emplace_back(Vec2d(rayEnd.getMinX(),rayEnd.getMaxY()),Vec2d(rayBegin.getMinX(),rayBegin.getMaxY()));
//    }
//    else if(dir.getX()>0 && dir.getY()>0){
//        edges.emplace_back(Vec2d(rayBegin.getMaxX(),rayBegin.getMinY()),Vec2d(rayBegin.getMinX(),rayBegin.getMaxY()));
//        edges.emplace_back(Vec2d(rayBegin.getMinX(),rayBegin.getMaxY()),Vec2d(rayEnd.getMinX(),rayEnd.getMaxY()));
//        edges.emplace_back(Vec2d(rayEnd.getMinX(),rayEnd.getMaxY()),Vec2d(rayEnd.getMaxX(),rayEnd.getMaxY()));
//        edges.emplace_back(Vec2d(rayEnd.getMaxX(),rayEnd.getMaxY()),Vec2d(rayEnd.getMaxX(),rayEnd.getMinY()));
//        edges.emplace_back(Vec2d(rayEnd.getMaxX(),rayEnd.getMinY()),Vec2d(rayBegin.getMaxX(),rayBegin.getMinY()));
//    }
//    else if(dir.getX()>0 && dir.getY()<0){
//        edges.emplace_back(Vec2d(rayBegin.getMinX(),rayBegin.getMinY()),Vec2d(rayBegin.getMaxX(),rayBegin.getMaxY()));
//        edges.emplace_back(Vec2d(rayBegin.getMaxX(),rayBegin.getMaxY()),Vec2d(rayEnd.getMaxX(),rayEnd.getMaxY()));
//        edges.emplace_back(Vec2d(rayEnd.getMaxX(),rayEnd.getMaxY()),Vec2d(rayEnd.getMaxX(),rayEnd.getMinY()));
//        edges.emplace_back(Vec2d(rayEnd.getMaxX(),rayEnd.getMinY()),Vec2d(rayEnd.getMinX(),rayEnd.getMinY()));
//        edges.emplace_back(Vec2d(rayEnd.getMinX(),rayEnd.getMinY()),Vec2d(rayBegin.getMinX(),rayBegin.getMinY()));
//    }
//    else if(dir.getX()<0 && dir.getY()>0){
//        edges.emplace_back(Vec2d(rayBegin.getMaxX(),rayBegin.getMaxY()),Vec2d(rayBegin.getMinX(),rayBegin.getMinY()));
//        edges.emplace_back(Vec2d(rayBegin.getMinX(),rayBegin.getMinY()),Vec2d(rayEnd.getMinX(),rayEnd.getMinY()));
//        edges.emplace_back(Vec2d(rayEnd.getMinX(),rayEnd.getMinY()),Vec2d(rayEnd.getMinX(),rayEnd.getMaxY()));
//        edges.emplace_back(Vec2d(rayEnd.getMinX(),rayEnd.getMaxY()),Vec2d(rayEnd.getMaxX(),rayEnd.getMaxY()));
//        edges.emplace_back(Vec2d(rayEnd.getMaxX(),rayEnd.getMaxY()),Vec2d(rayBegin.getMaxX(),rayBegin.getMaxY()));
//    }

    //与方块碰撞
    for(int x = (int)std::floor(rayUnion.getMinX()),endX = (int)std::ceil(rayUnion.getMaxX());x<=endX;x++){
        for(int y = (int)std::floor(rayUnion.getMinY()),endY = (int)std::ceil(rayUnion.getMaxY());y<=endY;y++){
//            Vec2d point(x+0.5,y+0.5);

            //斜线移动，环检测
//            bool flag = false;
//            for (auto &pair: edges){
//                Vec2d d = pair.second-pair.first;
//                if(point.isLeft(pair.first,d)){
//                    flag = true;
//                    break;
//                }
//            }
//            if(flag) continue;

            //判断(x+0.5,y+0.5)是否在
            //if(!isCloseToRay(Vec2d(x,y),startPoint,dir,maxDistance+xSize+ySize,xSize+ySize)) continue;
            auto block = getBlock(x,y,true);
            if(blockFilter(block->getMaterial()) && !MaterialHelper::isAir(block->getMaterial())){
                auto res = block->getBoundingBox().rayTrace(startPoint, dir, maxDistance, xSize, ySize);
                if(res.has_value()){
                    double len = (res->hitPoint-startPoint).lengthSquared();
                    if(len < minDistance){
                        minDistance = len;
                        closestPoint = res->hitPoint;
                        hitEntity = nullptr;
                        hitBlock = block;
                        hitFace = res->hitFace;
                    }
                }
            }
        }
    }
    if(!closestPoint.has_value()) return nullptr;
    return std::make_unique<RayTraceResult>(Location{name_,closestPoint->getX(),closestPoint->getY()},hitEntity,hitBlock,hitFace);
}

void World::run() {
    if(isRunning()) return;
    task_ = FlatCraft::getInstance()->getScheduler()->runTaskTimer([&](){
        ticks_++;
    },0,0);
}

void World::stop() {
    if(!isRunning()) return;
    task_->cancel();
    task_ = nullptr;
}

bool World::isRunning() const {
    return task_!= nullptr;
}

long long World::getTicks() const {
    return ticks_;
}

void World::setBlock(int x, int y, bool front, Material material) {
    int hash = (x<<11)^(y<<1)^front;
    blocks_[hash] = std::make_unique<Block>(material,Location(name_,x,y),front);
}

Weather World::getWeather() const {
    return weather_;
}

void World::setWeather(Weather weather) {
    weather_ = weather;
}


