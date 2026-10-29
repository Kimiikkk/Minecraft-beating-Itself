#include "entities.hpp"
Entity& Entities::add(Kind k,std::string n,Vec3 p,std::string d,RNG&){
    Entity e{nextId++,k,std::move(n),std::move(d),p,20,20,true,0};
    if(k==Kind::EnderDragon)e.hp=e.maxHp=200;
    if(k==Kind::EndCrystal)e.hp=e.maxHp=6;
    v.push_back(e);return v.back();
}
Entity* Entities::find(std::uint64_t id){for(auto&x:v)if(x.id==id)return &x;return nullptr;}
std::size_t Entities::alive(Kind k)const{std::size_t n=0;for(auto&x:v)if(x.alive&&x.kind==k)n++;return n;}
std::string kindName(Kind k){
switch(k){case Kind::Enderman:return"enderman";case Kind::SnowGolem:return"snow_golem";case Kind::Creeper:return"creeper";case Kind::EnderDragon:return"ender_dragon";case Kind::EndCrystal:return"end_crystal";case Kind::Villager:return"villager";default:return"other";}
}
