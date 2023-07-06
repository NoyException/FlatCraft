//
// Created by Noy on 2023/7/6.
//

#ifndef FLATCRAFT_CANCELABLE_H
#define FLATCRAFT_CANCELABLE_H

/**
 * 这是一个接口，继承该接口的类必须是Event的子类，代表了该事件可以被取消
 */
class Cancelable {
public:
    void setCanceled(bool canceled);
    [[nodiscard]] bool isCanceled() const;
private:
    bool canceled_;
};


#endif //FLATCRAFT_CANCELABLE_H
