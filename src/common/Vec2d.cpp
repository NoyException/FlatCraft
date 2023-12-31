//
// Created by Noy on 2023/7/6.
//

#include "Vec2d.h"
#include <cmath>

Vec2d::Vec2d() : x_(0), y_(0) {}

Vec2d::Vec2d(double x, double y) : x_(x), y_(y) {}

Vec2d::Vec2d(const nlohmann::json &json) :
Vec2d(json.at("x").get<double>(),json.at("y").get<double>()){}

Vec2d Vec2d::deserialize(const nlohmann::json& json){
    return Vec2d{json};
}

nlohmann::json Vec2d::serialize() const {
    return nlohmann::json{
            {"x",x_},
            {"y",y_}
    };
}

Vec2d &Vec2d::operator=(const Vec2d &another) = default;

Vec2d Vec2d::operator+(const Vec2d &another) const {
    return {x_+another.x_,y_+another.y_};
}

Vec2d Vec2d::operator-(const Vec2d &another) const {
    return {x_-another.x_,y_-another.y_};
}

Vec2d Vec2d::operator*(double a) const {
    return {x_*a,y_*a};
}

Vec2d Vec2d::operator/(double a) const {
    return {x_/a,y_/a};
}

bool Vec2d::operator==(const Vec2d &another) const {
    return x_ - another.x_ <= epsilon && x_ - another.x_ >= - epsilon && y_ - another.y_<= epsilon && y_ -another.y_ >= -epsilon;
}

bool Vec2d::operator!=(const Vec2d &another) const {
    return !(*this==another);
}

std::ostream &operator<<(std::ostream &out, const Vec2d &vec2D) {
    return out << "(" << vec2D.x_ << "," <<vec2D.y_ << ")";
}

double Vec2d::getX() const {
    return x_;
}

double Vec2d::getY() const {
    return y_;
}

int Vec2d::getBlockX() const {
    return std::floor(x_);
}

int Vec2d::getBlockY() const {
    return std::floor(y_);
}

Vec2d Vec2d::toBlockPosition() const {
    return {(double)getBlockX(),(double)getBlockY()};
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

void Vec2d::add(const Vec2d &another) {
    x_ += another.x_;
    y_ += another.y_;
}

void Vec2d::subtract(const Vec2d &another) {
    x_ -= another.x_;
    y_ -= another.y_;
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

bool Vec2d::isValid() const {
    return x_!=NAN && y_!=NAN;
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

double Vec2d::distanceSquared(const Vec2d &another) const {
    double dx = x_-another.x_;
    double dy = y_-another.y_;
    return dx*dx + dy*dy;
}

double Vec2d::distance(const Vec2d &another) const {
    return std::sqrt(distanceSquared(another));
}

bool Vec2d::isLeft(const Vec2d &start, const Vec2d &direction) const {
    // 如果叉积大于0，说明在直线的左侧
    return (*this - start).crossProduct(direction) > 0;
}

void Vec2d::adjust() {
    if(std::abs(x_-(int)x_)<epsilon) x_ = (int)x_;
    if(std::abs(y_-(int)y_)<epsilon) y_ = (int)y_;
}

void Vec2d::rotate(double angle) {
    double x0=x_;
    double y0=y_;
    x_=x0* cos(angle)- y0* sin(angle);
    y_=x0* sin(angle)+ y0* cos(angle);
}

void Vec2d::rotate(double angle, const Vec2d &center) {
    double x0=x_-center.x_;
    double y0=y_-center.y_;
    x_=x0* cos(angle)- y0* sin(angle)+center.x_;
    y_=x0* sin(angle)+ y0* cos(angle)+center.y_;
}

const double Vec2d::epsilon = 0.000001;












