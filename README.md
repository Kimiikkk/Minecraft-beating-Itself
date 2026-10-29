# Minecraft Self-Beating — Autonomous Progression Simulator

An event-driven Monte Carlo simulation that models autonomous Minecraft progression, from early-world events to entering the End and defeating the Ender Dragon.

## Overview

This project explores how a simulated Minecraft world can progress autonomously through a chain of stochastic events. A C++ simulation engine generates events, while a browser-based interface visualizes replay data.

This is a probabilistic macro-simulation inspired by the Minecraft "beats itself" experiment, not a full reimplementation of the Minecraft game engine.

## Features

- C++ simulation engine with event-driven progression.
- Stochastic waiting-time modeling and configurable random seeds.
- JSON Lines replay output for recording simulation events.
- Browser-based visualization of simulation replays.
- Event tracking for resource collection, world progression, the End, End Crystals, and Ender Dragon damage.
- Python utility for summarizing replay data.

## Technology Stack

- **C++17** — simulation engine.
- **HTML, CSS, JavaScript** — browser interface.
- **Python** — replay analysis utility.
- **JSON Lines (JSONL)** — simulation event and replay data.

## Project Structure

```text
Minecraft_Self_Beating_FROM_SCRATCH/
├── docs/                  # Project documentation
├── src/                   # C++ source code
├── web/                   # Browser interface
├── build_and_run.bat      # Windows build/run helper
├── summarize_replay.py    # Replay analysis utility
└── README.md
```

## Requirements

- Windows
- A C++17-compatible compiler, such as MinGW-w64 with `g++`
- A modern web browser
- Python, if using the replay analysis utility

## Build

Open PowerShell in the project directory and run:

```powershell
g++ -std=c++17 -O2 src\main.cpp src\config.cpp src\rng.cpp src\geometry.cpp src\world.cpp src\entities.cpp src\events.cpp src\simulator.cpp src\replay.cpp -o mc_self.exe
```

## Run a Simulation

Generate a replay using the executable:

```powershell
.\mc_self.exe --replay replay.jsonl
```

Run with a specific seed:

```powershell
.\mc_self.exe --seed -535646876083114041 --replay replay.jsonl
```

Limit the number of generated events:

```powershell
.\mc_self.exe --max-events 200000 --replay replay.jsonl
```

Open `web\index.html` in a browser and load the generated replay file if the interface prompts for one.

## Scientific Limitations

The simulator models a probabilistic sequence of events rather than reproducing every Minecraft game tick or the complete Java Edition server. Its behavior depends on the implemented rules, probability distributions, and simulation parameters.

Results should be interpreted as outputs of this model, not as verified predictions of actual Minecraft gameplay.

## Future Improvements

- Improve the realism and validation of event dependencies.
- Add richer simulation statistics and timeline controls.
- Expand replay analysis and visualization.
- Add automated tests and reproducible simulation comparisons.

## License

No license has been specified yet. All rights reserved unless a license is added to this repository.
