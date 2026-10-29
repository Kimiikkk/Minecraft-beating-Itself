#include "events.hpp"
std::string eventName(EventType t){
switch(t){
case EventType::WorldCreated:return"world_created";case EventType::PumpkinSpawned:return"pumpkin_spawned";
case EventType::PumpkinPicked:return"pumpkin_picked";case EventType::PumpkinTransferred:return"pumpkin_transferred";
case EventType::NearestOutpostLocated:return"nearest_outpost_located";case EventType::SnowGolemCreated:return"snow_golem_created";
case EventType::GolemProvokedCreeper:return"golem_provoked_creeper";case EventType::CreeperExplosion:return"creeper_explosion";
case EventType::RouteOpened:return"route_opened";case EventType::PortalReached:return"portal_reached";
case EventType::EndEntered:return"end_entered";case EventType::EndermanPlacedBlock:return"enderman_placed_block";
case EventType::SnowGolemEnteredEnd:return"snow_golem_entered_end";case EventType::CrystalDamaged:return"crystal_damaged";
case EventType::CrystalDestroyed:return"crystal_destroyed";case EventType::DragonDamage:return"dragon_damage";
case EventType::DragonDefeated:return"dragon_defeated";case EventType::Diagnostic:return"diagnostic";
}return"unknown";
}
