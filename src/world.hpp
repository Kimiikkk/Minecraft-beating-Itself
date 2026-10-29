#pragma once
#include "geometry.hpp"
#include "rng.hpp"
#include <string>
#include <vector>
struct Outpost {
    int id;
    Vec3 pos;
    long long pumpkinSupply;
    long long pumpkinsPicked=0;
};
struct Portal {
    Vec3 pos;
    bool active=true;
    bool routeOpen=false;
};
struct World {
    std::int64_t seed;
    Portal portal;
    std::vector<Outpost> outposts;
    Vec3 iceBiomeCenter;
    long long pumpkinsSpawned=0;
    long long pumpkinsPicked=0;
    long long pumpkinsNearPortal=0;
    long long golemsCreated=0;
    long long explosions=0;
    long long blocksRemoved=0;
    long long endermanPlacements=0;
    void generate(std::int64_t seed,RNG&rng);
    int nearestOutpost(const Vec3&p) const;
    double distanceToPortal(const Vec3&p) const;
    const Outpost& getOutpost(int id) const {return outposts.at(id);}
};
