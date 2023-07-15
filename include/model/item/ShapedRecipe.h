//
// Created by Noy on 2023/7/15.
//

#ifndef FLATCRAFT_SHAPEDRECIPE_H
#define FLATCRAFT_SHAPEDRECIPE_H

#include "Recipe.h"

class ShapedRecipe : public Recipe{
public:
    explicit ShapedRecipe(const nlohmann::json &json);
    bool match(const Material (&toMatch)[3][3]) const override;

private:
    Material getMaterial(int i, int j) const;
    std::vector<std::string> shape_;
    std::unordered_map<char,Material> mapping_;
};


#endif //FLATCRAFT_SHAPEDRECIPE_H
