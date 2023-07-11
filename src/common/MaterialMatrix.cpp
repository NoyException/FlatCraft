//
// Created by Noy on 2023/7/10.
//

#include "MaterialMatrix.h"

Material (*MaterialMatrix::operator[](int num))[2]{
    return matrix_[num];
}

std::shared_mutex &MaterialMatrix::getSharedMutex(){
    return mtx_;
}
Material* MaterialMatrix::getMatrix() {
    return reinterpret_cast<Material*> (matrix_);
}
