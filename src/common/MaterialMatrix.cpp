//
// Created by Noy on 2023/7/10.
//

#include "MaterialMatrix.h"

Material (*MaterialMatrix::operator[](int num))[2]{
    return matrix_[num];
}