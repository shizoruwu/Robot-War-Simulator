# Robot-War-Simulator
A turn-based robot battle simulator developed in C++ for the CCP6124 Object Oriented Programming and Data Structures assignment.
The simulator features autonomous robots battling in a grid-based arena using different movement, attack, and upgrade mechanics.

## Features
🤖 Multiple robot types with unique abilities
⚔️ Turn-based combat system
🧠 Object-Oriented Programming concepts:
- Inheritance
- Polymorphism
- Encapsulation
🔄 Robot upgrade system
🎯 Randomized battlefield interactions
📊 Battle status and robot statistics
🗺️ Grid-based battlefield simulation

## Technologies Used
Language: C++
Concepts: OOP, Data Structures
Project Structure
Robot-War-Simulator/
│
├── main.cpp              # Program entry point
├── Robot.h               # Base robot class
├── Robot.cpp
├── Battlefield.h         # Battlefield management
├── Battlefield.cpp
├── robots/               # Different robot types
├── upgrades/             # Upgrade system
├── input/                # Input configuration files
└── README.md

## Robot Types
Examples of robot categories included in the simulator:

Shooter Robot – attacks enemies from range
Moving Robot – navigates around the battlefield
Seeing Robot – scans nearby enemies

## Upgrade System
Robots can evolve during battle after achieving certain conditions.

Possible upgrades include:
- Increased attack power
- Improved movement
- Enhanced vision range

This creates dynamic gameplay where robots become stronger as the simulation progresses.

## How the Simulation Works
Robots are initialized on the battlefield.
Each robot takes turns performing actions:
Move
Scan
Shoot
Destroyed robots are removed from the battlefield.
The simulation continues until only one robot remains.
