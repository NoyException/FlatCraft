//
// Created by Noy on 2023/7/15.
//

#ifndef FLATCRAFT_RECIPE_H
#define FLATCRAFT_RECIPE_H

#include "common.h"
#include "ItemStackHelper.h"

class Recipe {
public:
    static void loadAllRecipes();
private:
    static void loadRecipe(std::string name);
    static std::list<std::unique_ptr<Recipe>> recipes_;
public:
    explicit Recipe(std::unique_ptr<ItemStack>&& result);
    virtual bool match(const Material (&toMatch)[3][3]) const = 0;
    std::unique_ptr<ItemStack> getResult();
private:
    std::unique_ptr<ItemStack> result_;
};


#endif //FLATCRAFT_RECIPE_H
