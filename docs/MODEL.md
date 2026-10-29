# Model

## Causal chain

1. Seeded world candidate
2. Pillager outposts contain carved-pumpkin opportunities
3. Endermen can pick up pumpkins
4. A pumpkin can be delivered into a snowy assembly area
5. A pumpkin + snow blocks can create a Snow Golem
6. Snow Golems provoke Creepers
7. Creeper explosions remove route blocks
8. Once the route is open, mobs can reach the completed End Portal
9. Endermen can wander in The End and manipulate blocks
10. Snow Golems can enter The End
11. Golem/projectile interactions can destroy End Crystals
12. Creeper explosions and golem projectiles can damage the Dragon
13. Every damage event is recorded until HP reaches zero

## Time model

The simulator does not execute every 20-tick Minecraft second for billions of
years. For each rare transition it samples a waiting time from an exponential
or log-normal hazard model. The state is still event-driven and causal.

This is the same broad mathematical strategy reported publicly for the original
experiment, but the exact hazard functions here are our own recreation.

## Calibration

The public timeline gives useful reference landmarks:
- first pumpkin pickup around year 33,477
- Snow Golem around 33,479
- route-opening explosions around 35,510–35,512
- End activity around 1.3 million
- first crystal around 3 million
- ninth crystal around 181 million
- last crystal around 199 million
- first dragon damage around 227 million
- defeat around 1.975 billion

These are NOT injected as events. They are used only to choose broad rate scales.
Different seeds/configurations can therefore produce different timelines.

## End Portal terminology
The model treats the End Portal as a world-generated structure. It records when the autonomous route first reaches/activates that portal; it does not claim that the portal itself was crafted from scratch by survival entities.
