#include "world.hpp"
#include <functional>
#include <algorithm>
void World::generate(std::int64_t s,RNG&rng){
    seed=s;
    // Deterministic seed-derived candidate world. The actual Minecraft terrain
    // generator is not embedded; this creates a reproducible spatial model.
    std::uint64_t h=static_cast<std::uint64_t>(s)^0x9e3779b97f4a7c15ULL;
    h^=h>>30; h*=0xbf58476d1ce4e5b9ULL; h^=h>>27;
    portal.pos={double((int)(h%1600)-800),28,double((int)((h>>16)%1600)-800)};
    iceBiomeCenter={portal.pos.x+rng.uniform(-120,120),64,portal.pos.z+rng.uniform(-120,120)};
    outposts.clear();
    // Outposts are the finite pumpkin-source inventory in this model.
    for(int i=0;i<18;i++){
        double a=rng.uniform(0.0,6.283185307);
        double r=rng.uniform(18000,62000);
        Outpost o;
        o.id=i;
        o.pos={portal.pos.x+std::cos(a)*r,64,portal.pos.z+std::sin(a)*r};
        o.pumpkinSupply=rng.integer(3000,12000);
        outposts.push_back(o);
        pumpkinsSpawned+=o.pumpkinSupply;
    }
    // Force one very distant source so the distance is meaningful and stable.
    if(!outposts.empty()){
        outposts[0].pos={portal.pos.x+41000,64,portal.pos.z+9000};
        outposts[0].pumpkinSupply=8000;
    }
}
int World::nearestOutpost(const Vec3&p)const{
    int best=0;double bd=1e100;
    for(const auto&o:outposts){double d=dist2(p,o.pos);if(d<bd){bd=d;best=o.id;}}
    return best;
}
double World::distanceToPortal(const Vec3&p)const{return dist(p,portal.pos);}
