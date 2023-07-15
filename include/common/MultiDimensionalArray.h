//
// Created by Noy on 2023/7/15.
//

#ifndef FLATCRAFT_MULTIDIMENSIONALARRAY_H
#define FLATCRAFT_MULTIDIMENSIONALARRAY_H

#include <stdexcept>

template<class T, int... lengths>
class MultiDimensionalArray{
public:

    MultiDimensionalArray();

    ~MultiDimensionalArray();

    template<int ...indexes>
    T get() const;

    template<int ...indexes>
    void set(const T& value);

private:
    template<int ...indexes>
    int getTotalIndex();
    int dimension_;
    int *lengths_;
    T *array_;
    int totalLength;
};

template<class T, int... lengths>
MultiDimensionalArray<T, lengths...>::MultiDimensionalArray() :
dimension_(sizeof...(lengths)), lengths_(new int[dimension_]{lengths...}), array_(nullptr), totalLength(0) {
    totalLength = 1;
    for (int i = 0; i < dimension_; ++i){
        totalLength *= lengths_[i];
    }
    array_ = new T[totalLength];
}

template<class T, int... lengths>
MultiDimensionalArray<T, lengths...>::~MultiDimensionalArray() {
    delete[] lengths_;
    delete[] array_;
}

template<class T, int... lengths>
template<int... indexes>
int MultiDimensionalArray<T, lengths...>::getTotalIndex() {
    if(sizeof...(indexes)!=dimension_)
        throw std::invalid_argument("indexes的数量与维度不匹配");
    int tmp[dimension_] = {indexes...};
    int index = 0;
    for (int i = 0; i < dimension_; ++i){
        index = index*lengths_[i] + tmp[i];
    }
    return index;
}

template<class T, int... lengths>
template<int... indexes>
T MultiDimensionalArray<T, lengths...>::get() const {
    return array_[getTotalIndex<indexes...>()];
}

template<class T, int... lengths>
template<int... indexes>
void MultiDimensionalArray<T, lengths...>::set(const T &value) {
    array_[getTotalIndex<indexes...>()] = value;
}

#endif //FLATCRAFT_MULTIDIMENSIONALARRAY_H
