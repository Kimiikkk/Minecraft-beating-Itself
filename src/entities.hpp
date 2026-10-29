#pragma once
#include "geometry.hpp"
#include "rng.hpp"
#include <cstdint>
#include <string>
#include <vector>
enum class Kind { Enderman,SnowGolem,Creeper,EnderDragon,EndCrystal,Villager,Other };
struct Entity {
    std::uint64_t id;
    Kind kind;
    std::string name;
    std::string dimension="overworld";
    Vec3 pos;
    double hp=20,maxHp=20;
    bool alive=true;
    std::uint64_t parent=0;
};
struct Entities {
    std::vector<Entity> v;
    std::uint64_t nextId=1;
    Entity& add(Kind k,std::string name,Vec3 p,std::string dim,RNG&rng);
    Entity* find(std::uint64_t id);
    std::size_t alive(Kind k)const;
};
std::string kindName(Kind k);
