//
// Created by Noy on 2023/7/6.
//

#include "util/Vec2d.h"

Vec2d::Vec2d() : x_(0), y_(0) {}

Vec2d::Vec2d(double x, double y) : x_(x), y_(y) {}

double Vec2d::getX() const {
    return x_;
}

double Vec2d::getY() const {
    return y_;
}

void Vec2d::setX(double x) {
    x_ = x;
}

void Vec2d::setY(double y) {
    y_ = y;
}

void Vec2d::add(double x, double y) {
    x_ += x;
    y_ += y;
}

void Vec2d::multiply(double m) {
    x_ *= m;
    y_ *= m;
}

void Vec2d::multiply(const Vec2d &another) {
    x_ *= another.x_;
    y_ *= another.y_;
}

void Vec2d::divide(const Vec2d &another) {
    x_ /= another.x_;
    y_ /= another.y_;
}

void Vec2d::normalize() {
    double len = length();
    x_ /= len;
    y_ /= len;
}

double Vec2d::dot(const Vec2d &another) const {
    return x_*another.x_ + y_*another.y_;
}

double Vec2d::crossProduct(const Vec2d &another) const {
    return x_*another.y_-y_*another.x_;
}

Vec2d Vec2d::midPoint(const Vec2d &another) const {
    return {(x_+another.x_)/2.0,(y_+another.y_)/2.0};
}

double Vec2d::lengthSquared() const {
    return x_*x_+y_*y_;
}

double Vec2d::length() const {
    return sqrt(x_*x_+y_*y_);
}

