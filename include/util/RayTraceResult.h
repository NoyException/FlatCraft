//
// Created by Noy on 2023/7/7.
//

#ifndef FLATCRAFT_RAYTRACERESULT_H
#define FLATCRAFT_RAYTRACERESULT_H

#include "common.h"
#include "Location.h"
#include "entity/Entity.h"

class RayTraceResult {
public:
    RayTraceResult(const Location &hitPoint, Entity *hitEntity, Block *hitBlock, BoundingBox::Face hitFace);
    [[nodiscard]] const Location* getHitPoint() const;
    [[nodiscard]] const Entity* getHitEntity() const;
    [[nodiscard]] const Block* getHitBlock() const;
    [[nodiscard]] BoundingBox::Face getHitFace() const;

private:
    Location hitPoint_;
    Entity* hitEntity_;
    Block* hitBlock_;
    BoundingBox::Face hitFace_;
};


#endif //FLATCRAFT_RAYTRACERESULT_H
