#include "simulator.hpp"
#include <iostream>
#include <algorithm>
#include <cmath>
Simulator::Simulator(const Config&c):cfg(c),rng(static_cast<std::uint64_t>(c.seed)),replay(c.replay){
    world.generate(c.seed,rng);
    replay.header(c.seed,world);
}
void Simulator::schedule(double y,EventType t,int st,const std::string&note){
    Event e;e.year=y;e.type=t;e.stage=st;e.note=note;q.push(e);
}
void Simulator::scheduleProgression(){
    // The entire run is one autonomous causal chain. We do not schedule the
    // WorldCreated event twice: main progression is seeded once from run().
    schedule(rng.lognormal(33477.0,0.42),EventType::PumpkinPicked,1,
             "Enderman picked up the first available carved pumpkin.");
}
void Simulator::emit(Event e){e.id=++eid;replay.write(e,world,es);if(cfg.verbose)std::cout<<e.id<<" | "<<e.year<<" | "<<eventName(e.type)<<" | "<<e.note<<"\n";}
void Simulator::process(const Event&e){
    now=e.year; Event x=e;
    switch(e.type){
    case EventType::WorldCreated: emit(x); scheduleProgression(); break;
    case EventType::PumpkinPicked:{
        // The first pumpkin is an actual sampled pickup. We separately compute
        // the geographically nearest outpost to the End Portal so the replay
        // can answer both questions: "where was the first pumpkin picked?"
        // and "which outpost was nearest to the portal?"
        int oi=rng.integer(0,(long long)world.outposts.size()-1);
        auto&o=world.outposts[oi];
        if(o.pumpkinSupply<=0){schedule(now+rng.exponential(10000),EventType::PumpkinPicked,1,"Retry: source outpost depleted.");break;}
        o.pumpkinSupply--;o.pumpkinsPicked++;world.pumpkinsPicked++;
        x.outpost=oi;x.pos=o.pos;x.distance=world.distanceToPortal(o.pos);x.count=world.pumpkinsPicked;
        if(world.pumpkinsPicked==1){
            int nearest=world.nearestOutpost(world.portal.pos);
            Event n; n.year=now; n.type=EventType::NearestOutpostLocated; n.stage=1;
            n.outpost=nearest; n.pos=world.outposts[nearest].pos;
            n.distance=world.distanceToPortal(n.pos);
            n.note="Nearest generated outpost to the End Portal identified for provenance tracking.";
            emit(n);
        }
        auto &em=es.add(Kind::Enderman,"Enderman #"+std::to_string(es.alive(Kind::Enderman)+1),o.pos,"overworld",rng);x.actor=em.id;
        emit(x);
        // Transfer probability increases if the pickup occurred in the snowy
        // candidate region. Distance matters because it controls travel time.
        double travel=std::max(2.0,world.distanceToPortal(o.pos)/1.2);
        schedule(now+rng.lognormal(travel,0.65),EventType::PumpkinTransferred,1,"Pumpkin moved toward the snow assembly area.");
        break;
    }
    case EventType::PumpkinTransferred:{
        world.pumpkinsNearPortal++;
        x.distance=world.distanceToPortal(world.iceBiomeCenter);x.pos=world.iceBiomeCenter;
        x.note="Pumpkin reached the modeled snowy assembly region.";
        emit(x);
        if(rng.chance(0.55)) schedule(now+rng.exponential(4.0),EventType::SnowGolemCreated,2,"Snow-golem construction condition satisfied.");
        else schedule(now+rng.lognormal(1200,1.1),EventType::PumpkinPicked,1,"Another pumpkin opportunity is sampled.");
        break;
    }
    case EventType::SnowGolemCreated:{
        world.golemsCreated++;auto&g=es.add(Kind::SnowGolem,"Snow Golem #"+std::to_string(world.golemsCreated),world.iceBiomeCenter,"overworld",rng);
        x.actor=g.id;x.pos=g.pos;x.count=world.golemsCreated;emit(x);
        schedule(now+rng.lognormal(2030.0,0.55),EventType::GolemProvokedCreeper,2,"Snow Golem projectile interaction with a Creeper.");
        break;
    }
    case EventType::GolemProvokedCreeper:{
        auto&c=es.add(Kind::Creeper,"Creeper #"+std::to_string(es.alive(Kind::Creeper)+1),world.iceBiomeCenter,"overworld",rng);
        x.actor=c.id;x.pos=c.pos;emit(x);
        schedule(now+rng.lognormal(1.8,0.35),EventType::CreeperExplosion,2,"Creeper detonated after being provoked.");
        break;
    }
    case EventType::CreeperExplosion:{
        world.explosions++;world.blocksRemoved+=rng.integer(6,18);x.pos=world.iceBiomeCenter;x.amount=world.blocksRemoved;
        emit(x);
        if(!route && world.explosions>=2){
            route=true;world.portal.routeOpen=true;
            schedule(now+rng.uniform(.1,3.0),EventType::RouteOpened,3,"Explosion sequence opened a continuous route toward the completed End Portal.");
        }else schedule(now+rng.lognormal(3000,0.9),EventType::SnowGolemCreated,2,"Further autonomous golem/Creeper interaction.");
        break;
    }
    case EventType::RouteOpened:{
        x.note="A chain of autonomous explosions opened the route toward the End Portal.";
        emit(x);
        schedule(now+rng.uniform(1,200),EventType::PortalReached,3,"A surface mob reached the completed End Portal.");
        break;
    }
    case EventType::PortalReached:{
        emit(x);schedule(now+rng.lognormal(1.3e6,0.35),EventType::EndEntered,4,"Mobs begin reaching The End through the open portal.");
        break;
    }
    case EventType::EndEntered:{
        endReached=true;x.pos={0,48,0};emit(x);spawnDragonAndCrystals();
        schedule(now+rng.lognormal(1.0e6,0.45),EventType::SnowGolemEnteredEnd,5,"A Snow Golem survives the route into The End.");
        schedule(now+rng.lognormal(1.0e6,0.35),EventType::EndermanPlacedBlock,4,"Endermen begin persistent block placement around the End island.");
        break;
    }
    case EventType::EndermanPlacedBlock:{
        world.endermanPlacements+=rng.integer(1,30);x.pos={rng.uniform(-80,80),rng.uniform(45,80),rng.uniform(-80,80)};
        emit(x);schedule(now+rng.lognormal(2.0e5,0.75),EventType::EndermanPlacedBlock,4,"Further Enderman block placement.");
        break;
    }
    case EventType::SnowGolemEnteredEnd:{
        auto&g=es.add(Kind::SnowGolem,"End Snow Golem #"+std::to_string(world.golemsCreated+1),{rng.uniform(-60,60),48,rng.uniform(-60,60)},"end",rng);
        x.actor=g.id;x.pos=g.pos;emit(x);
        schedule(now+rng.lognormal(3.0e6,0.75),EventType::CrystalDamaged,6,"Snowball/projectile interaction reached an End Crystal.");
        break;
    }
    case EventType::CrystalDamaged:{
        x.pos={rng.uniform(-45,45),rng.uniform(65,100),rng.uniform(-45,45)};x.amount=rng.uniform(1,6);emit(x);
        if(rng.chance(.72))schedule(now+rng.exponential(100),EventType::CrystalDestroyed,6,"Crystal received enough accidental damage.");
        else schedule(now+rng.lognormal(2.5e6,0.8),EventType::CrystalDamaged,6,"Another projectile reaches a crystal.");
        break;
    }
    case EventType::CrystalDestroyed:{
        crystalsDestroyed++;
        // Destroy one real simulated crystal entity and record its ID.
        for(auto &cr : es.v){
            if(cr.kind==Kind::EndCrystal && cr.alive){
                cr.alive=false; x.target=cr.id; x.pos=cr.pos; break;
            }
        }
        x.count=crystalsDestroyed;
        x.note="End Crystal destroyed. Crystal "+std::to_string(crystalsDestroyed)+" / 10.";
        emit(x);
        if(crystalsDestroyed<10) schedule(now+rng.lognormal(18.0e6,0.85),EventType::CrystalDamaged,6,"Search for another crystal-damaging interaction.");
        else schedule(now+rng.lognormal(28.0e6,0.45),EventType::DragonDamage,7,"All crystals have been destroyed; the first damaging interaction is sampled.");
        break;
    }
    case EventType::DragonDamage:{
        auto*d=es.find(dragonId);if(!d||!d->alive)break;
        double dmg=rng.uniform(.5,6.0);
        if(rng.chance(.03))dmg+=rng.uniform(8,20);
        d->hp=std::max(0.0,d->hp-dmg);x.actor=dragonId;x.amount=dmg;x.pos=d->pos;
        x.note="Dragon damage: -"+std::to_string(dmg)+" HP; remaining "+std::to_string(d->hp)+" HP.";
        emit(x);
        if(d->hp<=0){
            d->alive=false;dead=true;
            Event death; death.year=now; death.type=EventType::DragonDefeated; death.stage=8;
            death.actor=dragonId; death.amount=200.0; death.pos=d->pos;
            death.note="Ender Dragon health reached zero after the recorded damage event.";
            emit(death);
        } else schedule(now+rng.lognormal(2.8e6,0.85),EventType::DragonDamage,7,"Another accidental dragon-damage opportunity.");
        break;
    }
    case EventType::DragonDefeated:emit(x);break;
    default:emit(x);break;
    }
}
void Simulator::spawnDragonAndCrystals(){
    auto&d=es.add(Kind::EnderDragon,"Ender Dragon",{0,64,0},"end",rng);dragonId=d.id;
    for(int i=0;i<10;i++)es.add(Kind::EndCrystal,"End Crystal #"+std::to_string(i+1),{rng.uniform(-45,45),rng.uniform(70,105),rng.uniform(-45,45)},"end",rng);
}
void Simulator::run(){
    schedule(0,EventType::WorldCreated,0,"Autonomous world initialized from the supplied seed.");
    while(!q.empty() && eid<cfg.maxEvents){
        Event e=q.pop();if(e.year>cfg.maxYears)break;
        process(e);
        if(dead)break;
    }
    if(!dead){Event d;d.year=now;d.type=EventType::Diagnostic;d.note="Maximum simulation horizon reached before dragon defeat.";emit(d);}
}
