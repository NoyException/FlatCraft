//
// Created by Noy on 2023/7/7.
//

#ifndef FLATCRAFT_BOUNDINGBOX_H
#define FLATCRAFT_BOUNDINGBOX_H

#include "Vec2d.h"
#include <optional>

struct BoundingBoxRayTraceResult;

class BoundingBox {
public:
    enum class Face : unsigned char{
        TOP,
        BOTTOM,
        LEFT,
        RIGHT
    };
    BoundingBox(double minX, double minY, double maxX, double maxY);
    BoundingBox(const Vec2d& a, const Vec2d& b);
    BoundingBox(const BoundingBox& another);
    [[nodiscard]] double getMinX() const;
    void setMinX(double minX);
    [[nodiscard]] double getMinY() const;
    void setMinY(double minY);
    [[nodiscard]] double getMaxX() const;
    void setMaxX(double maxX);
    [[nodiscard]] double getMaxY() const;
    void setMaxY(double maxY);
    [[nodiscard]] double getWidth() const;
    [[nodiscard]] double getHeight() const;
    [[nodiscard]] double getCenterX() const;
    [[nodiscard]] double getCenterY() const;
    [[nodiscard]] Vec2d getCenter() const;
    [[nodiscard]] bool isCollidable() const;
    void expand(double negativeX, double negativeY, double positiveX, double positiveY);
    [[nodiscard]] bool contains(double x,double y) const;
    [[nodiscard]] bool contains(const Vec2d& v) const;
    [[nodiscard]] bool contains(const BoundingBox& another) const;
    [[nodiscard]] bool overlaps(const BoundingBox& another) const;
    void shift(double x,double y);
    void union_(const BoundingBox& another);
    void intersection(const BoundingBox& another);
    [[nodiscard]] std::optional<BoundingBoxRayTraceResult> rayTrace(const Vec2d& startPoint, const Vec2d& direction, double maxDistance) const;
    [[nodiscard]] std::optional<BoundingBoxRayTraceResult> rayTrace(const Vec2d& startPoint, const Vec2d& direction, double maxDistance, double xSize, double ySize) const;
    friend std::ostream& operator<<(std::ostream& out, const BoundingBox& aabb);
private:
    void adjust(const Vec2d& center);
    double minX_;
    double minY_;
    double maxX_;
    double maxY_;
};

struct BoundingBoxRayTraceResult{
    Vec2d hitPoint;
    BoundingBox::Face hitFace;
};

#endif //FLATCRAFT_BOUNDINGBOX_H
