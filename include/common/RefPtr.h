//
// Created by Noy on 2023/7/11.
//

#ifndef FLATCRAFT_REFPTR_H
#define FLATCRAFT_REFPTR_H

template<class T>
class RefPtr {
public:
    RefPtr(T *&t) : t_(t) {}
    void pointTo(T& t);
private:
    T*& t_;
};

template<class T>
void RefPtr<T>::pointTo(T &t) {
    t_ = &t;
}


#endif //FLATCRAFT_REFPTR_H
