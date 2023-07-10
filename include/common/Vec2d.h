//
// Created by Noy on 2023/7/6.
//

#ifndef FLATCRAFT_VEC2D_H
#define FLATCRAFT_VEC2D_H

#include <ostream>

class Vec2d {
public:
    Vec2d();
    Vec2d(const Vec2d& another) = default;
    Vec2d(double x, double y);
    Vec2d& operator=(const Vec2d& another);
    Vec2d operator+(const Vec2d& another) const;
    Vec2d operator-(const Vec2d& another) const;
    Vec2d operator*(double a) const;
    Vec2d operator/(double a) const;
    bool operator==(const Vec2d& another) const;
    bool operator!=(const Vec2d& another) const;
    friend std::ostream& operator<<(std::ostream& out, const Vec2d& vec2D);
    [[nodiscard]] double getX() const;
    [[nodiscard]] double getY() const;
    [[nodiscard]] int getBlockX() const;
    [[nodiscard]] int getBlockY() const;
    void setX(double x);
    void setY(double y);
    void add(double x, double y);
    void add(const Vec2d& another);
    void subtract(const Vec2d& another);
    void multiply(double m);
    void multiply(const Vec2d& another);
    void divide(const Vec2d& another);
    [[nodiscard]] bool isValid() const;
    void normalize();
    [[nodiscard]] double dot(const Vec2d& another) const;
    [[nodiscard]] double crossProduct(const Vec2d& another) const;
    [[nodiscard]] Vec2d midPoint(const Vec2d& another) const;
    [[nodiscard]] double lengthSquared() const;
    [[nodiscard]] double length() const;
    [[nodiscard]] bool isLeft(const Vec2d& start, const Vec2d& direction) const;
    void rotate(double angle);
    void rotate(double angle ,const Vec2d& center);
    void adjust();
    friend class BoundingBox;
    static const double epsilon;
private:
    double x_;
    double y_;
};


#endif //FLATCRAFT_VEC2D_H
