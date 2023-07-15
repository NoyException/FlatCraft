//
// Created by Noy on 2023/7/15.
//

#include "model/item/Recipe.h"

Recipe::Recipe(std::unique_ptr<ItemStack> &&result) : result_(std::move(result)) {}

std::unique_ptr<ItemStack> Recipe::getResult() {
    return result_->clone();
}
