//
// Created by Noy on 2023/7/10.
//

#ifndef FLATCRAFT_MATERIALMATRIX_H
#define FLATCRAFT_MATERIALMATRIX_H

#include "Material.h"
#include <shared_mutex>

class MaterialMatrix {
public:
    static const int MAX_ROW = 28;
    static const int MAX_COLUMN = 42;
    Material (*operator[](int num))[2];
    std::shared_mutex &getSharedMutex();
    Material* getMatrix();
private:
    Material matrix_[MAX_COLUMN][MAX_ROW][2];
    std::shared_mutex mtx_;
};


#endif //FLATCRAFT_MATERIALMATRIX_H
