//
// Created by Noy on 2023/7/3.
//

#ifndef FLATCRAFT_LOCATION_H
#define FLATCRAFT_LOCATION_H

#include "common.h"

class Location {
public:
    Location(const std::shared_ptr<World>& world, double x, double y);
    Location(const Location& location);
    bool operator==(const Location& another) const;
    [[nodiscard]] std::shared_ptr<World> getWorld() const;
    [[nodiscard]] double getX() const;
    [[nodiscard]] double getY() const;
    [[nodiscard]] int getBlockX() const;
    [[nodiscard]] int getBlockY() const;
    void setWorld(const std::shared_ptr<World>& world);
    void setX(double x);
    void setY(double y);
    void add(const Location& another);
    [[nodiscard]] double distanceSquared(const Location& another) const;
    [[nodiscard]] double distance(const Location& another) const;
private:
    std::shared_ptr<World> world_;
    double x_,y_;
};


#endif //FLATCRAFT_LOCATION_H
