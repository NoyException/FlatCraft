//
// Created by Noy on 2023/7/13.
//

#ifndef FLATCRAFT_VIEWMODEL_H
#define FLATCRAFT_VIEWMODEL_H


class ViewModel {
public:
    [[nodiscard]] bool isBound() const;
    void notifyBound();
protected:
    virtual void onBound() = 0;
private:
    bool bound_ = false;
};


#endif //FLATCRAFT_VIEWMODEL_H
