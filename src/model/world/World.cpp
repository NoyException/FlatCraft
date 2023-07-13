//
// Created by Noy on 2023/7/3.
//

#include "model/world/World.h"
#include "model/FlatCraft.h"
#include "model/world/WorldGenerator.h"
#include "model/entity/entities.h"


World::World(const std::string& name, long long seed) :
name_(name), ticks_(0), weather_(Weather::CLEAR), seed_(seed), rand_(seed) {
    init();
}

World::World(const nlohmann::json &json) :
name_(json.at("name").get<std::string>()),
ticks_(json.at("ticks").get<long long>()),
weather_(static_cast<Weather>(json.at("weather").get<int>())),
seed_(json.at("seed").get<long long>()),
rand_(json.at("randomSeed").get<unsigned long long>()){
    auto blocks = json.at("blocks");
    for(int i=-128;i<=128;i++) {
        for (int j = 0; j < 256; j++) {
            for(int k = 0; k <= 1; k++) {
                std::stringstream ss;
                ss << i << "_" << j << "_" << k;
                Block block = Block::deserialize(Location(name_, i, j),
                                                 k,blocks.at(ss.str()));
                int hash = (i << 11) ^ (j << 1) ^ k;
                blocks_[hash] = std::make_unique<Block>(block);
            }
        }
    }
}

std::unique_ptr<nlohmann::json> World::serialize() const {
    auto json = std::make_unique<nlohmann::json>(nlohmann::json::initializer_list_t{
        {"name",name_},
        {"ticks",ticks_},
        {"seed",seed_},
        {"weather",static_cast<int>(weather_)},
        {"randomSeed",rand_.getCurrentSeed()}
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
    json->emplace("blocks",std::move(blocks));
    return json;
}

std::unique_ptr<World> World::deserialize(const nlohmann::json &json) {
    return std::make_unique<World>(json);
}

std::string World::getName() const {
    return name_;
}

Block* World::getBlock(int x, int y, bool front) const {
    auto it = blocks_.find((x<<11)^(y<<1)^front);
    if(it==blocks_.end()) return nullptr;
    return it->second.get();
}

Block *World::getBlock(const Vec2d &v, bool front) const {
    return getBlock(v.getBlockX(),v.getBlockY(),front);
}

Block* World::getBlock(const Location &location, bool front) const {
    if(location.getRawWorld()!=name_) return nullptr;
    return getBlock(location.getBlockX(), location.getBlockY(), front);
}

void World::notifyEntityJoin(Entity *entity) {
    entities_.insert(entity);
}

void World::notifyEntityLeave(Entity *entity) {
    entities_.erase(entity);
}

void World::getEntities(std::vector<Entity*> &entities) const {
    for (const auto &item: entities_){
        entities.push_back(item);
    }
}

void World::getEntities(std::vector<Entity*> &entities, const std::function<bool(const Entity&)>& filter) const {
    for (const auto &item: entities_){
        if(filter(*item)) entities.push_back(item);
    }
}

void World::getEntitiesNearby(std::vector<Entity *> &entities, const Vec2d& position, double r, const std::function<bool(const Entity&)>& filter) const {
    getEntities(entities, [&](const Entity& entity){
        return entity.getLocation().toVec2d().distanceSquared(position)<=r*r && filter(entity);
    });
}

void World::init() {
    seed_ = (int)(rand_.nextInt()%INT_MAX);
    WorldGenerator generator;
    generator.generate(*this);
    /*for(int i=-128;i<=128;i++){
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
    for(int i=5;i<=10;i++){
        for(int j=60;j<64;j++){
            setBlock(i,j,true,Material::WATER);
            setBlock(i,j,false,Material::WATER);
        }
    }*/
//    setBlock(4,64, true,Material::DIRT);
//    setBlock(4,64, false,Material::WATER);
//    setBlock(5,64, true,Material::DIRT);
//    setBlock(6,64, false,Material::DIRT);
}

void World::run() {
    std::cout<<"world "<<name_<<" start ticking"<<std::endl;
    if(isRunning()) return;
    task_ = FlatCraft::getInstance()->getScheduler()->runTaskTimer([&](){
        ticks_++;
        ValueChangedNotification notification(this,Field::WORLD_TICKS,ticks_);
        EventManager::callEvent(notification);
        if(ticks_%1200==0){
            if(rand_.nextDouble()<0.2){
                switch (weather_) {
                    case Weather::CLEAR:
                        if(rand_.nextDouble()<0.2)
                            setWeather(Weather::THUNDERSTORM);
                        else
                            setWeather(Weather::RAIN);
                        break;
                    case Weather::RAIN:
                        setWeather(Weather::CLEAR);
                        break;
                    case Weather::THUNDERSTORM:
                        if(rand_.nextDouble()<0.4)
                            setWeather(Weather::CLEAR);
                        else
                            setWeather(Weather::RAIN);
                }
            }
        }
    },0,0);
}

void World::stop() {
    std::cout<<"world "<<name_<<" stop ticking"<<std::endl;
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
    WorldWeatherChangeEvent event(this, weather);
    EventManager::callEvent(event);
    if(event.isCanceled()) return;
    ValueChangedNotification notification(this,Field::WORLD_WEATHER,weather);
    EventManager::callEvent(notification);
    weather_ = weather;
}

std::unique_ptr<RayTraceResult> World::rayTrace(const Vec2d& startPoint, const Vec2d &direction,
                                                double maxDistance, double xSize, double ySize, bool hitBackground,
                                                const std::function<bool(Block*)>& blockFilter,
                                                const std::function<bool(Entity*)>& entityFilter) const {
    if(direction.getX()==0 && direction.getY()==0) return nullptr;
    Vec2d dir = direction;
    dir.normalize();
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
            for(int front = 1; front>0 || (front>=0 && hitBackground); front--){
                auto block = getBlock(x,y,front);
                if(blockFilter(block) && !MaterialHelper::isAir(block->getMaterial())){
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
    }
    if(!closestPoint.has_value()) return nullptr;
    return std::make_unique<RayTraceResult>(Location{name_,closestPoint->getX(),closestPoint->getY()},hitEntity,hitBlock,hitFace);
}

std::unique_ptr<RayTraceResult> World::rayTrace(const Location &location, const Vec2d &direction,
                                                double maxDistance, double xSize, double ySize, bool hitBackground,
                                                const std::function<bool(Block*)>& blockFilter,
                                                const std::function<bool(Entity*)>& entityFilter) const {
    return rayTrace(location.toVec2d(), direction, maxDistance, xSize, ySize, hitBackground, blockFilter, entityFilter);
}

long long World::getSeed() const {
    return seed_;
}

void World::dropItem(const Vec2d &position, std::unique_ptr<ItemStack>&& itemStack) {
    auto item = FlatCraft::getInstance()->createEntity<DroppedItem>(std::move(itemStack));
    item->teleport(Location(*this,position.getX(),position.getY()));
    item->setVelocity({rand_.nextDouble()/5.0-0.1,0.1});
}


