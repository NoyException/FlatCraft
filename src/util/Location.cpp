//
// Created by Noy on 2023/7/3.
//

#include "Location.h"
#include "world/World.h"
#include "FlatCraft.h"

Location::Location(std::string world, double x, double y) : world_(std::move(world)), x_(x), y_(y) {}

Location::Location(const World& world, double x, double y) : world_(world.getName()), x_(x), y_(y){}

Location::Location(const Location &location) = default;

Location &Location::operator=(const Location &another) = default;

bool Location::operator==(const Location &another) const {
    return world_==another.world_ && x_ == another.x_ && y_ == another.y_;
}

bool Location::operator<(const Location &another) const {
    int res = world_.compare(another.world_);
    if(res<0) return true;
    else if(res==0){
        if(x_<another.x_) return true;
        else if(x_==another.x_) return y_<another.y_;
    }
    return false;
}

std::ostream& operator<<(std::ostream& out, const Location& location){
    return out << "[" << location.world_ << ":(" << location.x_ << ", " << location.y_ << ")]";
}

World* Location::getWorld() const {
    return FlatCraft::getInstance()->getWorld(world_);
}

Block *Location::getBlock(bool front) const {
    auto world = getWorld();
    if(world== nullptr) return nullptr;
    return world->getBlock(getBlockX(),getBlockY(),front);
}

double Location::getX() const {
    return x_;
}

double Location::getY() const {
    return y_;
}

int Location::getBlockX() const {
    return (int) round(x_);
}

int Location::getBlockY() const {
    return (int) round(y_);
}

void Location::setWorld(const World &world) {
    world_ = world.getName();
}

void Location::setX(double x) {
    x_ = x;
}

void Location::setY(double y) {
    y_ = y;
}

void Location::add(double x, double y) {
    x_ += x;
    y_ += y;
}

void Location::add(const Vec2d &v) {
    x_ += v.getX();
    y_ += v.getY();
}

void Location::add(const Location &another) {
    x_ += another.x_;
    y_ += another.y_;
}

double Location::distanceSquared(const Location &another) const {
    double dx = x_-another.x_;
    double dy = y_-another.y_;
    return dx*dx + dy*dy;
}

double Location::distance(const Location &another) const {
    return sqrt(distanceSquared(another));
}

Location Location::toBlockLocation() const {
    return {world_, (double)getBlockX(), (double)getBlockY()};
}

std::string Location::getRawWorld() const {
    return world_;
}

Location Location::deserialize(const nlohmann::json &json) {
    return {
        json.at("world").get<std::string>(),
        json.at("x").get<double>(),
        json.at("y").get<double>()
    };
}

nlohmann::json Location::serialize() const {
    return nlohmann::json{
            {"world",world_},
            {"x",x_},
            {"y",y_}
    };
}

Vec2d Location::toVec2d() const {
    return {x_,y_};
}

void Location::adjust() {
    if(abs(x_-(int)x_)<0.000001) x_ = (int)x_;
    if(abs(y_-(int)y_)<0.000001) y_ = (int)y_;
}


