@echo off
setlocal

g++ -std=c++17 -O2 src\main.cpp src\config.cpp src\rng.cpp src\geometry.cpp src\world.cpp src\entities.cpp src\events.cpp src\simulator.cpp src\replay.cpp -o mc_self.exe
if errorlevel 1 (
  echo Build failed.
  pause
  exit /b 1
)

mc_self.exe --replay replay.jsonl --max-events 10000 --max-years 10000000000
if errorlevel 1 (
  echo Simulation failed.
  pause
  exit /b 1
)

python summarize_replay.py replay.jsonl
pause
