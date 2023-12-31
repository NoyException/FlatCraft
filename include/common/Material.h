//
// Created by Noy on 2023/7/3.
//

#ifndef FLATCRAFT_MATERIAL_H
#define FLATCRAFT_MATERIAL_H

#include <set>
#include <unordered_map>
#include "json.hpp"

enum class Material : int {
    AIR = 0,
    STONE = 1,
    GRASS = 2,
    DIRT = 3,
    PLANKS = 5,
    BED_ROCK = 7,
    WATER = 9,
    COAL_ORE = 16,
    LOG = 17,
    LEAVES = 18
};

enum class MaterialFlag{
    OCCLUDED,
    SOLID,
    AIR,
    LIQUID,
};

class MaterialInfo{
public:
    static MaterialInfo deserialize(const std::string& name, const nlohmann::json& json);
    int id_{};
    std::string name_{};
    int maxStacks_{};
    double hardness_{};
    double antiExplosion_{};
    std::set<MaterialFlag> flags_;
    std::set<std::string> tools_;
private:
    MaterialInfo(int id, int maxStacks, double hardness, double antiExplosion);
};

class MaterialHelper{
public:
    static void registerAllMaterials();
    static void getAllMaterials(std::vector<Material>& container);
    static MaterialInfo *getInfo(Material material);
    static Material getByName(const std::string& name);
    static std::string getName(Material material);
    static bool containsFlag(Material material, MaterialFlag flag);
    static bool isOccluded(Material material);
    static bool isSolid(Material material);
    static bool isAir(Material material);
    static bool isLiquid(Material material);
    static double getHardness(Material material);
private:
    static std::unordered_map<int,MaterialInfo> byId;
    static std::unordered_map<std::string,MaterialInfo> byName;
    static void registerMaterial(const std::string& name);
};

#endif //FLATCRAFT_MATERIAL_H
