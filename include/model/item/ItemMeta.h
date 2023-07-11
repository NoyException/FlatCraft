//
// Created by Noy on 2023/7/9.
//

#ifndef FLATCRAFT_ITEMMETA_H
#define FLATCRAFT_ITEMMETA_H

#include "common.h"
#include "Item.h"

class ItemMeta {
public:
    virtual ~ItemMeta() = default;
    static std::unique_ptr<ItemMeta> ofDefault(Item* item);
};


#endif //FLATCRAFT_ITEMMETA_H