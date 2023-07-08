//
// Created by Noy on 2023/7/7.
//

#ifndef FLATCRAFT_BOUNDINGBOX_H
#define FLATCRAFT_BOUNDINGBOX_H

#include "Vec2d.h"
#include "RayTraceResult.h"

class BoundingBox {
public:
    BoundingBox(double minX, double minY, double maxX, double maxY);
    BoundingBox(const Vec2d& a, const Vec2d& b);

    [[nodiscard]] double getMinX() const;
    void setMinX(double minX);
    [[nodiscard]] double getMinY() const;
    void setMinY(double minY);
    [[nodiscard]] double getMaxX() const;
    void setMaxX(double maxX);
    [[nodiscard]] double getMaxY() const;
    void setMaxY(double maxY);
    [[nodiscard]] double getCenterX() const;
    [[nodiscard]] double getCenterY() const;
    [[nodiscard]] Vec2d getCenter() const;
    [[nodiscard]] bool contains(double x,double y) const;
    [[nodiscard]] bool contains(const Vec2d& v) const;
    [[nodiscard]] bool contains(const BoundingBox& another) const;
    [[nodiscard]] bool overlaps(const BoundingBox& another) const;
    void shift(double x,double y);
    void union_(const BoundingBox& another);
    void intersection(const BoundingBox& another);
//    std::unique_ptr<RayTraceResult> rayTrace(const Location& startPoint, const Vec2d& direction, );
private:
    double minX_;
    double minY_;
    double maxX_;
    double maxY_;
};


#endif //FLATCRAFT_BOUNDINGBOX_H
