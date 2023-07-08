//
// Created by Noy on 2023/7/7.
//

#include "util/BoundingBox.h"

#define min(a,b) ((a)>(b)?(b):(a))
#define max(a,b) ((a)>(b)?(a):(b))

BoundingBox::BoundingBox(double minX, double minY, double maxX, double maxY) : minX_(minX), minY_(minY), maxX_(maxX),
                                                                               maxY_(maxY) {}

BoundingBox::BoundingBox(const Vec2d &a, const Vec2d &b):
        minX_(min(a.getX(), b.getX())), minY_(min(a.getY(), b.getY())), maxX_(max(a.getX(), b.getX())), maxY_(max(a.getY(), b.getY())){}

double BoundingBox::getMinX() const {
    return minX_;
}

void BoundingBox::setMinX(double minX) {
    minX_ = minX;
}

double BoundingBox::getMinY() const {
    return minY_;
}

void BoundingBox::setMinY(double minY) {
    minY_ = minY;
}

double BoundingBox::getMaxX() const {
    return maxX_;
}

void BoundingBox::setMaxX(double maxX) {
    maxX_ = maxX;
}

double BoundingBox::getMaxY() const {
    return maxY_;
}

void BoundingBox::setMaxY(double maxY) {
    maxY_ = maxY;
}

double BoundingBox::getCenterX() const {
    return (maxX_+minX_)/2;
}

double BoundingBox::getCenterY() const {
    return (maxY_+minY_)/2;
}

Vec2d BoundingBox::getCenter() const {
    return {getCenterX(),getCenterY()};
}

bool BoundingBox::contains(double x, double y) const {
    return x >= minX_ && x < maxX_ && y >= minY_ && y < maxY_;
}

bool BoundingBox::contains(const Vec2d &v) const {
    return contains(v.getX(),v.getY());
}

bool BoundingBox::contains(const BoundingBox &another) const {
    return minX_<=another.minX_ && minY_<=another.minY_ && maxX_>=another.maxX_ && maxY_>=another.maxY_;
}

bool BoundingBox::overlaps(const BoundingBox &another) const {
    return minX_<another.maxX_ && maxX_>another.minX_ && minY_<another.maxY_ && maxY_>another.minY_;
}

void BoundingBox::shift(double x, double y) {
    maxX_+=x;
    maxY_+=y;
    minX_+=x;
    minY_+=y;
}

void BoundingBox::union_(const BoundingBox &another) {
    maxX_= max(another.maxX_,maxX_);
    maxY_= max(another.maxY_,maxY_);
    minX_= min(another.minX_,minX_);
    minY_= min(another.minY_,minY_);
}

void BoundingBox::intersection(const BoundingBox &another) {
    maxX_= min(maxX_,another.maxX_);
    minX_= max(minX_,another.minX_);
    maxY_= min(maxY_,another.maxY_);
    minY_= max(minY_,another.minY_);
}
