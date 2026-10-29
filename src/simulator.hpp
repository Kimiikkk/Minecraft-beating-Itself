#pragma once
#include "config.hpp"
#include "rng.hpp"
#include "world.hpp"
#include "entities.hpp"
#include "events.hpp"
#include "queue.hpp"
#include "replay.hpp"
class Simulator {
    Config cfg; RNG rng; World world; Entities es; EventQueue q; Replay replay;
    double now=0; std::uint64_t eid=0; bool route=false,endReached=false,dead=false;
    std::uint64_t dragonId=0; int crystalsDestroyed=0;
    void schedule(double year,EventType t,int stage,const std::string&note);
    void scheduleProgression();
    void process(const Event&);
    void emit(Event e);
    void spawnDragonAndCrystals();
public:
    explicit Simulator(const Config&c);
    void run();
};
