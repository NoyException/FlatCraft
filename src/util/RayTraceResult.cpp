//
// Created by Noy on 2023/7/7.
//

#include "util/RayTraceResult.h"

const Location* RayTraceResult::getHitPoint() const {
    return &hitPoint_;
}

const Entity *RayTraceResult::getHitEntity() const {
    return hitEntity_;
}

const Block *RayTraceResult::getHitBlock() const {
    return hitBlock_;
}

BoundingBox::Face RayTraceResult::getHitFace() const {
    return hitFace_;
}

RayTraceResult::RayTraceResult(const Location &hitPoint, Entity *hitEntity, Block *hitBlock, BoundingBox::Face hitFace)
: hitPoint_(hitPoint), hitEntity_(hitEntity), hitBlock_(hitBlock), hitFace_(hitFace) {}
