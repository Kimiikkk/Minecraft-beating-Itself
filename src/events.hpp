#pragma once
#include "geometry.hpp"
#include <cstdint>
#include <string>
enum class EventType {
    WorldCreated,PumpkinSpawned,PumpkinPicked,PumpkinTransferred,NearestOutpostLocated,
    SnowGolemCreated,GolemProvokedCreeper,CreeperExplosion,RouteOpened,PortalReached,
    EndEntered,EndermanPlacedBlock,SnowGolemEnteredEnd,CrystalDamaged,CrystalDestroyed,
    DragonDamage,DragonDefeated,Diagnostic
};
struct Event {
    double year=0;
    std::uint64_t id=0;
    EventType type;
    int stage=0;
    Vec3 pos;
    Vec3 secondary;
    std::uint64_t actor=0,target=0;
    long long count=0;
    double amount=0;
    double distance=0;
    int outpost=-1;
    std::string note;
};
struct Compare { bool operator()(const Event&a,const Event&b)const{return a.year>b.year;} };
std::string eventName(EventType);
