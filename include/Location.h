//
// Created by Noy on 2023/7/3.
//

#ifndef FLATCRAFT_LOCATION_H
#define FLATCRAFT_LOCATION_H

#include "common.h"

class World;
class Block;

class Location {
public:
    friend struct LocationHash;
    Location(std::string world, double x, double y);
    Location(const World &world, double x, double y);
    Location(const Location& location);
    static Location deserialize(const nlohmann::json& json);
    [[nodiscard]] nlohmann::json serialize() const;
    Location& operator=(const Location& another);
    bool operator==(const Location& another) const;
    bool operator<(const Location& another) const;
    [[nodiscard]] Vec2d toVec2d() const;
    [[nodiscard]] World* getWorld() const;
    [[nodiscard]] Block* getBlock(bool front) const;
    [[nodiscard]] std::string getRawWorld() const;
    [[nodiscard]] double getX() const;
    [[nodiscard]] double getY() const;
    [[nodiscard]] int getBlockX() const;
    [[nodiscard]] int getBlockY() const;
    [[nodiscard]] Location toBlockLocation() const;
    void setWorld(const World &world);
    void setX(double x);
    void setY(double y);
    void add(double x, double y);
    void add(const Location& another);
    [[nodiscard]] double distanceSquared(const Location& another) const;
    [[nodiscard]] double distance(const Location& another) const;
private:
    std::string world_;
    double x_,y_;
};

struct LocationHash {
    size_t operator()(const Location& location) const {
        return std::hash<std::string>()(location.world_) ^
               std::hash<double>()(location.x_) ^ std::hash<double>()(location.y_);
    }
};

#endif //FLATCRAFT_LOCATION_H
