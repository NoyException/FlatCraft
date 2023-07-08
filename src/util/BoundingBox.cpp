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
// Vec2d是一个二维向量类，可以进行加减乘除等运算
// std::optional是一个模板类，可以表示有值或者无值的情况
std::optional<Vec2d> BoundingBox::rayTrace(const Vec2d& startPoint, const Vec2d& direction,
                                           double maxDistance, double raySize) const {
    Vec2d dir = direction;
    dir.normalize();
    // 计算射线和边界框的四个交点
    std::optional<Vec2d> leftIntersect, rightIntersect, topIntersect, bottomIntersect;
    // 如果射线不垂直于x轴
    if (dir.x_ != 0) {
        // 计算与左边界的交点
        double t1 = (minX_ - startPoint.x_) / dir.x_;
        if (t1 >= 0 && t1 <= maxDistance) {
            double y1 = startPoint.y_ + t1 * dir.y_;
            if (y1 >= minY_ - raySize && y1 <= maxY_ + raySize) {
                leftIntersect = Vec2d(minX_, y1);
            }
        }
        // 计算与右边界的交点
        double t2 = (maxX_ - startPoint.x_) / dir.x_;
        if (t2 >= 0 && t2 <= maxDistance) {
            double y2 = startPoint.y_ + t2 * dir.y_;
            if (y2 >= minY_ - raySize && y2 <= maxY_ + raySize) {
                rightIntersect = Vec2d(maxX_, y2);
            }
        }
    }
    // 如果射线不垂直于y轴
    if (dir.y_ != 0) {
        // 计算与上边界的交点
        double t3 = (maxY_ - startPoint.y_) / dir.y_;
        if (t3 >= 0 && t3 <= maxDistance) {
            double x3 = startPoint.x_ + t3 * dir.x_;
            if (x3 >= minX_ - raySize && x3 <= maxX_ + raySize) {
                topIntersect = Vec2d(x3, maxY_);
            }
        }
        // 计算与下边界的交点
        double t4 = (minY_ - startPoint.y_) / dir.y_;
        if (t4 >= 0 && t4 <= maxDistance) {
            double x4 = startPoint.x_ + t4 * dir.x_;
            if (x4 >= minX_ - raySize && x4 <= maxX_ + raySize) {
                bottomIntersect = Vec2d(x4, minY_);
            }
        }
    }
    // 筛选有效的交点
    std::vector<std::optional<Vec2d>> validIntersects;
    if (leftIntersect) validIntersects.push_back(leftIntersect);
    if (rightIntersect) validIntersects.push_back(rightIntersect);
    if (topIntersect) validIntersects.push_back(topIntersect);
    if (bottomIntersect) validIntersects.push_back(bottomIntersect);
    // 如果没有有效的交点，返回空值
    if (validIntersects.empty()) return std::nullopt;
    // 找出距离起点最近的交点
    std::optional<Vec2d> closestIntersect = validIntersects[0];
    double minDistance = (startPoint - closestIntersect.value()).length();
    for (int i = 1; i < validIntersects.size(); i++) {
        double distance = (startPoint - validIntersects[i].value()).length();
        if (distance < minDistance) {
            closestIntersect = validIntersects[i];
            minDistance = distance;
        }
    }
    // 返回最终的相交点
    return closestIntersect;
}