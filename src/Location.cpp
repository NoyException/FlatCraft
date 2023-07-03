//
// Created by Noy on 2023/7/3.
//

#include "Location.h"

Location::Location(const std::shared_ptr<World> &world, double x, double y) : world_(world), x_(x), y_(y){}

Location::Location(const Location &location) : world_(location.world_), x_(location.x_), y_(location.y_) {}

bool Location::operator==(const Location &another) const {
    return world_==another.world_ && x_ == another.x_ && y_ == another.y_;
}

std::shared_ptr<World> Location::getWorld() const {
    return world_;
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

void Location::setWorld(const std::shared_ptr<World> &world) {
    world_ = world;
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