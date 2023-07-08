//
// Created by Noy on 2023/7/7.
//

#include "util/BoundingBox.h"
#include <vector>

#define min(a,b) ((a)>(b)?(b):(a))
#define max(a,b) ((a)>(b)?(a):(b))

BoundingBox::BoundingBox(double minX, double minY, double maxX, double maxY) : minX_(minX), minY_(minY), maxX_(maxX),
                                                                               maxY_(maxY) {}

BoundingBox::BoundingBox(const Vec2d &a, const Vec2d &b):
        minX_(min(a.getX(), b.getX())), minY_(min(a.getY(), b.getY())), maxX_(max(a.getX(), b.getX())), maxY_(max(a.getY(), b.getY())){}

BoundingBox::BoundingBox(const BoundingBox &another) = default;

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
/*
std::optional<Vec2d>
BoundingBox::rayTrace(const Vec2d &startPoint, const Vec2d &direction, double maxDistance, double raySize) const {
    double y0=startPoint.getY();
    double x0=startPoint.getX();
    Vec2d nordirection=direction;
    nordirection.normalize();
    double xfinal=maxDistance*nordirection.getX()+x0;
    double yfinal=maxDistance*nordirection.getY()+x0;
    Vec2d rayA(x0-raySize*nordirection.getY(),y0+raySize*nordirection.getX());
    Vec2d rayB(x0+raySize*nordirection.getY(),y0-raySize*nordirection.getX());

    return std::optional<Vec2d>();

}*/

// 假设BoundingBox的成员变量是double类型
std::optional<Vec2d> BoundingBox::rayTrace(const Vec2d& startPoint, const Vec2d& direction,
                                           double maxDistance, double raySize) const {
    // 检查射线是否与包围盒相交，如果不相交则返回空值
    double tmin = (minX_ - startPoint.x_) / direction.x_;
    double tmax = (maxX_ - startPoint.x_) / direction.x_;
    if (tmin > tmax) std::swap(tmin, tmax); // 保证tmin <= tmax
    double tymin = (minY_ - startPoint.y_) / direction.y_;
    double tymax = (maxY_ - startPoint.y_) / direction.y_;
    if (tymin > tymax) std::swap(tymin, tymax); // 保证tymin <= tymax
    if (tmin > tymax || tymin > tmax) return std::nullopt; // 射线与包围盒不相交
    // 计算射线与包围盒的交点，取最近的一个
    double t = max(tmin, tymin);
    if (t < 0 || t > maxDistance) return std::nullopt; // 射线起点在包围盒外或超出最大距离
    Vec2d hitPoint = startPoint + direction * t; // 射线与包围盒的交点
    // 检查交点是否在包围盒的边界上，如果是则返回交点，否则返回空值
    if (hitPoint.x_ == minX_ || hitPoint.x_ == maxX_) { // 射线与包围盒的左右边界相交
        hitPoint.y_ = startPoint.y_ + direction.y_ / direction.x_ * t; // 根据射线方程计算hitPoint.y_
        if (std::abs(hitPoint.y_ - minY_) <= raySize / 2 || std::abs(hitPoint.y_ - maxY_) <= raySize / 2) { // 考虑射线的宽度
            return hitPoint;
        }
        else {
            return std::nullopt;
        }
    }
    else if (hitPoint.y_ == minY_ || hitPoint.y_ == maxY_) { // 射线与包围盒的上下边界相交
        hitPoint.x_ = startPoint.x_ + direction.x_ / direction.y_ * t; // 根据射线方程计算hitPoint.x_
        if (std::abs(hitPoint.x_ - minX_) <= raySize / 2 || std::abs(hitPoint.x_ - maxX_) <= raySize / 2) { // 考虑射线的宽度
            return hitPoint;
        }
        else {
            return std::nullopt;
        }
    }
    else { // 射线与包围盒的内部相交，这种情况不应该发生，但为了安全起见还是返回空值
        return std::nullopt;
    }
}


std::ostream &operator<<(std::ostream &out, const BoundingBox &aabb) {
    return out<<"[("<<aabb.minX_<<","<<aabb.minY_<<"),("<<aabb.maxX_<<","<<aabb.maxY_<<")]";
}
