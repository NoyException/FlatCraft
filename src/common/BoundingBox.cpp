//
// Created by Noy on 2023/7/7.
//

#include "BoundingBox.h"
#include <vector>
#include <cmath>

inline bool doubleEqual(const double& a, const double& b){
    return a-b<0.000001 && b-a<0.000001;
}

BoundingBox::BoundingBox(double minX, double minY, double maxX, double maxY) : minX_(minX), minY_(minY), maxX_(maxX),
                                                                               maxY_(maxY) {}

BoundingBox::BoundingBox(const Vec2d &a, const Vec2d &b):
        minX_(std::min(a.getX(), b.getX())), minY_(std::min(a.getY(), b.getY())), maxX_(std::max(a.getX(), b.getX())), maxY_(std::max(a.getY(), b.getY())){}

BoundingBox::BoundingBox(const BoundingBox &another) = default;

BoundingBox &BoundingBox::operator=(const BoundingBox &another) = default;

BoundingBox BoundingBox::operator+(const BoundingBox &another) const {
    return {
        std::min(minX_,another.minX_),
        std::min(minY_,another.minY_),
        std::max(maxX_,another.maxX_),
        std::max(maxY_,another.maxY_)
    };
}

BoundingBox BoundingBox::operator*(const BoundingBox &another) const {
    BoundingBox aabb = another;
    aabb.union_(*this);
    return aabb;
}

BoundingBox BoundingBox::operator+(const Vec2d &shift) const {
    return {minX_+shift.x_,minY_+shift.y_,maxX_+shift.x_,maxY_+shift.y_};
}

BoundingBox BoundingBox::operator-(const Vec2d &shift) const {
    return {minX_-shift.x_,minY_-shift.y_,maxX_-shift.x_,maxY_-shift.y_};
}

double BoundingBox::getMinX() const {
    return minX_;
}

void BoundingBox::setMinX(double minX) {
    minX_ = std::min(minX,maxX_);
}

double BoundingBox::getMinY() const {
    return minY_;
}

void BoundingBox::setMinY(double minY) {
    minY_ = std::min(minY,maxY_);
}

double BoundingBox::getMaxX() const {
    return maxX_;
}

void BoundingBox::setMaxX(double maxX) {
    maxX_ = std::max(maxX,minX_);
}

double BoundingBox::getMaxY() const {
    return maxY_;
}

void BoundingBox::setMaxY(double maxY) {
    maxY_ = std::max(maxY,minY_);
}

double BoundingBox::getWidth() const {
    return maxX_-minX_;
}

double BoundingBox::getHeight() const {
    return maxY_-minY_;
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

bool BoundingBox::isCollidable() const {
    return minX_<maxX_ && minY_<maxY_;
}

void BoundingBox::expand(double negativeX, double negativeY, double positiveX, double positiveY) {
    auto center = getCenter();
    minX_ -= negativeX;
    minY_ -= negativeY;
    maxX_ += positiveX;
    maxY_ += positiveY;
    adjust(center);
}

bool BoundingBox::contains(double x, double y) const {
    return x >= minX_ && x <= maxX_ && y >= minY_ && y <= maxY_;
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

void BoundingBox::shift(const Vec2d &v) {
    shift(v.x_,v.y_);
}

void BoundingBox::union_(const BoundingBox &another) {
    maxX_= std::max(another.maxX_,maxX_);
    maxY_= std::max(another.maxY_,maxY_);
    minX_= std::min(another.minX_,minX_);
    minY_= std::min(another.minY_,minY_);
}

void BoundingBox::intersection(const BoundingBox &another) {
    Vec2d center = getCenter().midPoint(another.getCenter());
    maxX_= std::min(maxX_,another.maxX_);
    minX_= std::max(minX_,another.minX_);
    maxY_= std::min(maxY_,another.maxY_);
    minY_= std::max(minY_,another.minY_);
    adjust(center);
}

std::optional<BoundingBoxRayTraceResult> BoundingBox::rayTrace(const Vec2d& startPoint, const Vec2d& direction,
                                           double maxDistance) const {
    if(!isCollidable()) return std::nullopt;
    double epsilon = 0.000001;
    BoundingBox tmp = *this;
    tmp.expand(-epsilon,-epsilon,-epsilon,-epsilon);
    //在碰撞箱内，不检测
    if(tmp.contains(startPoint))
        return std::nullopt;
    //在碰撞箱表面或者外面，如果不朝着里面走就不碰撞
    if((doubleEqual(startPoint.getX(),minX_) && direction.getX()<=0)
    || (doubleEqual(startPoint.getX(),maxX_) && direction.getX()>=0)
    || (doubleEqual(startPoint.getY(),minY_) && direction.getY()<=0)
    || (doubleEqual(startPoint.getY(),maxY_) && direction.getY()>=0))
        return std::nullopt;

//    if(!((doubleEqual(startPoint.getX(),minX_) && direction.getX()>0 && startPoint.getY()>minY_+epsilon && startPoint.getY()<maxY_-epsilon)
//         || (doubleEqual(startPoint.getX(),maxX_) && direction.getX()<0 && startPoint.getY()>minY_+epsilon && startPoint.getY()<maxY_-epsilon)
//         || (doubleEqual(startPoint.getY(),minY_) && direction.getY()>0 && startPoint.getX()>minX_+epsilon && startPoint.getX()<maxX_-epsilon)
//         || (doubleEqual(startPoint.getY(),maxY_) && direction.getY()<0 && startPoint.getX()>minX_+epsilon && startPoint.getX()<maxX_-epsilon)
//    )) return std::nullopt;

    Vec2d dir = direction;
    dir.normalize();
    // 计算射线和边界框的四个交点
    std::optional<Vec2d> leftIntersect, rightIntersect, topIntersect, bottomIntersect;
    // 如果射线不垂直于x轴
    if (std::abs(dir.x_) > epsilon) {
        // 计算与左边界的交点
        double t1 = (minX_ - startPoint.x_) / dir.x_;
        if (t1 >= -epsilon && t1 <= maxDistance+epsilon) {
            double y1 = startPoint.y_ + t1 * dir.y_;
            if (y1 >= minY_ && y1 <= maxY_) {
                leftIntersect = Vec2d(minX_, y1);
            }
        }
        // 计算与右边界的交点
        double t2 = (maxX_ - startPoint.x_) / dir.x_;
        if (t2 >= -epsilon && t2 <= maxDistance+epsilon) {
            double y2 = startPoint.y_ + t2 * dir.y_;
            if (y2 >= minY_ && y2 <= maxY_) {
                rightIntersect = Vec2d(maxX_, y2);
            }
        }
    }
    // 如果射线不垂直于y轴
    if (std::abs(dir.y_) > epsilon) {
        // 计算与上边界的交点
        double t3 = (maxY_ - startPoint.y_) / dir.y_;
        if (t3 >= -epsilon && t3 <= maxDistance+epsilon) {
            double x3 = startPoint.x_ + t3 * dir.x_;
            if (x3 >= minX_ && x3 <= maxX_) {
                topIntersect = Vec2d(x3, maxY_);
            }
        }
        // 计算与下边界的交点
        double t4 = (minY_ - startPoint.y_) / dir.y_;
        if (t4 >= -epsilon && t4 <= maxDistance+epsilon) {
            double x4 = startPoint.x_ + t4 * dir.x_;
            if (x4 >= minX_ && x4 <= maxX_) {
                bottomIntersect = Vec2d(x4, minY_);
            }
        }
    }
    // 筛选有效的交点
    std::vector<BoundingBoxRayTraceResult> validIntersects;
    if (leftIntersect) validIntersects.push_back({leftIntersect.value(),Face::LEFT});
    if (rightIntersect) validIntersects.push_back({rightIntersect.value(),Face::RIGHT});
    if (topIntersect) validIntersects.push_back({topIntersect.value(),Face::TOP});
    if (bottomIntersect) validIntersects.push_back({bottomIntersect.value(),Face::BOTTOM});
    // 如果没有有效的交点，返回空值
    if (validIntersects.empty()) return std::nullopt;
    // 找出距离起点最近的交点
    BoundingBoxRayTraceResult* closestIntersect = &validIntersects[0];
    double minDistance = (startPoint - closestIntersect->hitPoint).lengthSquared();
    for (int i = 1; i < validIntersects.size(); i++) {
        double distance = (startPoint - validIntersects[i].hitPoint).lengthSquared();
        if (distance < minDistance) {
            closestIntersect = &validIntersects[i];
            minDistance = distance;
        }
    }
    // 返回最终的相交点
    return *closestIntersect;
}

std::optional<BoundingBoxRayTraceResult> BoundingBox::rayTrace(const Vec2d& startPoint, const Vec2d& direction,
                                           double maxDistance, double xSize, double ySize) const {
    if(!isCollidable()) return std::nullopt;
    BoundingBox aabb = *this;
    aabb.expand(xSize,ySize,xSize,ySize);
    return aabb.rayTrace(startPoint, direction, maxDistance);
}

std::ostream &operator<<(std::ostream &out, const BoundingBox &aabb) {
    return out<<"[("<<aabb.minX_<<","<<aabb.minY_<<"),("<<aabb.maxX_<<","<<aabb.maxY_<<")]";
}

void BoundingBox::adjust(const Vec2d &center) {
    double x = std::isnan(center.x_) || std::isinf(center.x_) ? 0 : center.x_;
    double y = std::isnan(center.y_) || std::isinf(center.y_) ? 0 : center.y_;
    if(std::isnan(minX_) || std::isinf(minX_) || minX_>x) minX_=x;
    if(std::isnan(minY_) || std::isinf(minY_) || minY_>y) minX_=y;
    if(std::isnan(maxX_) || std::isinf(maxX_) || maxX_<x) maxX_=x;
    if(std::isnan(maxY_) || std::isinf(maxY_) || maxY_<y) maxY_=y;
}
