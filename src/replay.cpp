#include "replay.hpp"
#include "events.hpp"
#include "entities.hpp"
#include <iomanip>
std::string Replay::esc(const std::string&s){std::string r;for(char c:s){if(c=='"')r+="\\\"";else if(c=='\\')r+="\\\\";else if(c=='\n')r+="\\n";else r+=c;}return r;}
void Replay::header(std::int64_t seed,const World&w){
f<<"{\"kind\":\"header\",\"version\":3,\"seed\":"<<seed
<<",\"portal\":{\"x\":"<<w.portal.pos.x<<",\"y\":"<<w.portal.pos.y<<",\"z\":"<<w.portal.pos.z<<"}}\n";
}
void Replay::write(const Event&e,const World&w,const Entities&es){
long long crystals=0; for(auto&x:es.v)if(x.kind==Kind::EndCrystal&&x.alive)crystals++;
double dragon=200; for(auto&x:es.v)if(x.kind==Kind::EnderDragon)dragon=x.hp;
f<<std::setprecision(15)<<"{\"kind\":\"event\",\"year\":"<<e.year<<",\"id\":"<<e.id
<<",\"type\":\""<<eventName(e.type)<<"\",\"stage\":"<<e.stage
<<",\"x\":"<<e.pos.x<<",\"y\":"<<e.pos.y<<",\"z\":"<<e.pos.z
<<",\"sx\":"<<e.secondary.x<<",\"sy\":"<<e.secondary.y<<",\"sz\":"<<e.secondary.z
<<",\"actor\":"<<e.actor<<",\"target\":"<<e.target<<",\"count\":"<<e.count
<<",\"amount\":"<<e.amount<<",\"distance\":"<<e.distance<<",\"outpost\":"<<e.outpost
<<",\"note\":\""<<esc(e.note)<<"\",\"state\":{"
<<"\"pumpkinsSpawned\":"<<w.pumpkinsSpawned<<",\"pumpkinsPicked\":"<<w.pumpkinsPicked
<<",\"pumpkinsNearPortal\":"<<w.pumpkinsNearPortal<<",\"golemsCreated\":"<<w.golemsCreated
<<",\"explosions\":"<<w.explosions<<",\"blocksRemoved\":"<<w.blocksRemoved
<<",\"endermanPlacements\":"<<w.endermanPlacements<<",\"crystalsAlive\":"<<crystals
<<",\"dragonHp\":"<<dragon<<"},\"outposts\":[";
for(std::size_t i=0;i<w.outposts.size();i++){
if(i)f<<",";
auto&o=w.outposts[i];
f<<"{\"id\":"<<o.id<<",\"x\":"<<o.pos.x<<",\"y\":"<<o.pos.y<<",\"z\":"<<o.pos.z
<<",\"pumpkinSupply\":"<<o.pumpkinSupply<<",\"pumpkinsPicked\":"<<o.pumpkinsPicked
<<",\"distanceToPortal\":"<<dist(o.pos,w.portal.pos)<<"}";
}
f<<"],\"entities\":[";
bool first=true;for(auto&x:es.v){if(!first)f<<",";first=false;
f<<"{\"id\":"<<x.id<<",\"kind\":\""<<kindName(x.kind)<<"\",\"name\":\""<<esc(x.name)
<<"\",\"dimension\":\""<<x.dimension<<"\",\"x\":"<<x.pos.x<<",\"y\":"<<x.pos.y<<",\"z\":"<<x.pos.z
<<",\"hp\":"<<x.hp<<",\"alive\":"<<(x.alive?"true":"false")<<"}";
}
f<<"]}\n";
}
