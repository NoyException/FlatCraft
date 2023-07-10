//
// Created by Noy on 2023/7/3.
//

#ifndef FLATCRAFT_BLOCKDATA_H
#define FLATCRAFT_BLOCKDATA_H

#include "common.h"

class BlockData {
public:
    [[nodiscard]] nlohmann::json serialize() const;
    static BlockData deserialize(const nlohmann::json& json);
};


#endif //FLATCRAFT_BLOCKDATA_H
