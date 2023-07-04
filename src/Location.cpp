//
// Created by Noy on 2023/7/3.
//

#include "Location.h"
#include "world/World.h"
#include "FlatCraft.h"

Location::Location(std::string world, double x, double y) : world_(std::move(world)), x_(x), y_(y) {}

Location::Location(const World& world, double x, double y) : world_(world.getName()), x_(x), y_(y){}

Location::Location(const Location &location) = default;

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

World* Location::getWorld() const {
    return FlatCraft::getInstance()->getWorld(world_);
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

