# Zork - Text Adventure Game (C++ Edition)

A classic text-based adventure game inspired by the original Zork, written in modern C++17. Navigate through mysterious locations, collect items, solve puzzles, and battle enemies through immersive text commands.

## Table of Contents

- [Quick Start](#quick-start)
- [Features](#features)
- [Installation](#installation)
- [Building from Source](#building-from-source)
- [Docker Deployment](#docker-deployment)
- [Kubernetes Deployment](#kubernetes-deployment)
- [How to Play](#how-to-play)
- [Project Structure](#project-structure)
- [Architecture](#architecture)
- [Development](#development)
- [Required Enhancements](#required-enhancements)
- [Contributing](#contributing)

---

## Quick Start

### Option 1: Build and Run Locally

```bash
./scripts/build.sh
./scripts/run.sh
```

### Option 2: Run with Docker

```bash
./scripts/docker-build.sh
./scripts/docker-run.sh
```

### Option 3: Deploy to Kubernetes

```bash
./scripts/deploy-k8s.sh
kubectl exec -it <pod-name> -- /app/zork
```

---

## Features

### Current Features

✅ **Core Gameplay**
- Room-based navigation with interconnected locations
- Rich, descriptive environments
- Interactive command parser with alias support
- Real-time inventory management with weight system

✅ **Combat System**
- Enemy encounters with AI behavior
- Turn-based combat mechanics
- Health and damage calculations
- Critical hit system

✅ **Item System**
- Multiple item types (weapons, armor, keys, consumables)
- Item properties (weight, damage, defense)
- Context-aware item interactions

✅ **Game Mechanics**
- Scoring system with achievements
- Room discovery tracking
- Dark room mechanics (requires light source)
- Locked door system

✅ **Technical Features**
- Modern C++17 codebase
- CMake build system
- Docker containerization
- Kubernetes deployment ready
- JSON data files for game content
- Save/load game structure (ready for implementation)

---

## Installation

### Prerequisites

**Required:**
- C++17 compatible compiler (GCC 9+, Clang 10+, or MSVC 2019+)
- CMake 3.15 or higher
- Make or Ninja build system

**Optional:**
- Docker (for containerized deployment)
- Kubernetes cluster (for orchestrated deployment)

### System-Specific Setup

**Ubuntu/Debian:**
```bash
sudo apt-get update
sudo apt-get install build-essential cmake
```

**macOS:**
```bash
xcode-select --install
brew install cmake
```

**Windows:**
- Install Visual Studio 2019+ with C++ tools, or
- Install MinGW-w64 and CMake

---

## Building from Source

### Quick Build

```bash
./scripts/build.sh
```

This creates a `build` directory and compiles the project in Release mode.

### Build Options

**Debug Build:**
```bash
./scripts/build.sh --debug
```

**Clean Build (remove previous build artifacts):**
```bash
./scripts/build.sh --clean
```

### Manual Build

```bash
mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j$(nproc)
```

The executable will be at `build/zork`.

### Running the Game

**Using the script:**
```bash
./scripts/run.sh
```

**Manual execution:**
```bash
./build/zork
```

---

## Docker Deployment

### Building the Docker Image

**Using the script:**
```bash
./scripts/docker-build.sh
```

**With custom tag:**
```bash
./scripts/docker-build.sh --tag v1.0.0
```

**Manual build:**
```bash
docker build -t zork:latest .
```

### Running in Docker

**Using the script:**
```bash
./scripts/docker-run.sh
```

**Manual run:**
```bash
docker run -it --rm \
  --name zork-game \
  -v $(pwd)/saves:/app/saves \
  -e TERM=xterm-256color \
  zork:latest
```

### Docker Compose

**Start the game:**
```bash
docker-compose up -d
```

**Attach to the running container:**
```bash
docker attach zork-game
```

**Stop the game:**
```bash
docker-compose down
```

---

## Kubernetes Deployment

### Prerequisites

- Kubernetes cluster (minikube, kind, GKE, EKS, AKS, etc.)
- kubectl configured to access your cluster

### Deploy to Kubernetes

**Using the script:**
```bash
./scripts/deploy-k8s.sh
```

**With custom namespace:**
```bash
./scripts/deploy-k8s.sh --namespace games
```

**Manual deployment:**
```bash
kubectl apply -f kubernetes/configmap.yaml
kubectl apply -f kubernetes/pvc.yaml
kubectl apply -f kubernetes/deployment.yaml
```

### Access the Game

**List pods:**
```bash
kubectl get pods
```

**Execute the game:**
```bash
kubectl exec -it zork-deployment-<pod-id> -- /app/zork
```

### Remove Deployment

```bash
./scripts/deploy-k8s.sh --delete
```

---

## How to Play

### Basic Commands

**Movement:**
- `north`, `south`, `east`, `west`, `up`, `down` (or `n`, `s`, `e`, `w`, `u`, `d`)
- `go <direction>` - Alternative movement syntax

**Observation:**
- `look` or `l` - View current room description
- `examine <item>` or `x <item>` - Look at an item closely

**Item Interaction:**
- `take <item>` or `get <item>` - Pick up an item
- `drop <item>` - Drop an item from inventory
- `use <item>` - Use an item
- `inventory` or `i` - View items you're carrying

**Combat:**
- `attack <enemy>` or `kill <enemy>` - Attack an enemy
- `fight <enemy>` - Engage in combat

**Game Management:**
- `score` - View your current score
- `save` - Save your game progress
- `load` - Load a saved game
- `help` or `?` - Display available commands
- `quit` or `exit` - Exit the game

### Sample Gameplay

```
> look
West of House
You are standing in an open field west of a white house, with a boarded front door. 
There is a small mailbox here.

You see: mailbox, leaflet
Exits: north, south

> take leaflet
You take the leaflet.

> examine leaflet
A small leaflet that reads: 'Welcome to Zork!'

> south
Behind House
You are behind the white house.

> east
Kitchen
You are in the kitchen of the white house.

You see: lamp
Exits: west, east, up, down

> take lamp
You take the lamp.

> inventory
You are carrying:
  - leaflet (1 lbs)
  - lamp (3 lbs)
Total weight: 4/100 lbs

> up
Attic
This is the attic.

You see: rope
Exits: down

> score
Your current score is 20 points.
```

### Game World Locations

- **West of House** - Starting location with mailbox
- **Forest** - North of starting area (maze-like navigation)
- **Behind House** - South of starting location
- **Kitchen** - Central hub with multiple exits
- **Living Room** - East of kitchen
- **Attic** - Up from kitchen
- **Cellar** - Down from kitchen (dark, requires light)

### Available Items

- **Leaflet** - Welcome message
- **Lamp** - Provides light in dark areas
- **Rope** - Useful for climbing puzzles
- **Sword** - Weapon for combat (+15 damage)
- **Key** - Unlocks certain doors
- **Mailbox** - Cannot be taken (fixed object)

---

## Project Structure

```
zork/
├── include/                  # Header files
│   ├── Constants.h          # Game constants and configuration
│   ├── Item.h               # Item class definition
│   ├── Room.h               # Room class definition
│   ├── Player.h             # Player class definition
│   ├── Enemy.h              # Enemy class definition
│   ├── Command.h            # Command parser
│   ├── Game.h               # Main game controller
│   ├── Utils.h              # Utility functions
│   └── SaveManager.h        # Save/load functionality
│
├── src/                      # Implementation files
│   ├── main.cpp             # Entry point
│   ├── Game.cpp             # Game logic
│   ├── Room.cpp             # Room implementation
│   ├── Item.cpp             # Item implementation
│   ├── Player.cpp           # Player implementation
│   ├── Enemy.cpp            # Enemy implementation
│   ├── Command.cpp          # Command parsing
│   ├── Utils.cpp            # Utility implementations
│   └── SaveManager.cpp      # Save/load implementation
│
├── data/                     # JSON game data
│   ├── rooms.json           # Room definitions
│   ├── items.json           # Item definitions
│   └── enemies.json         # Enemy definitions
│
├── kubernetes/               # Kubernetes manifests
│   ├── deployment.yaml      # Deployment configuration
│   ├── pvc.yaml            # Persistent volume claims
│   └── configmap.yaml      # Configuration data
│
├── scripts/                  # Build and deployment scripts
│   ├── build.sh            # Build the project
│   ├── run.sh              # Run the game
│   ├── docker-build.sh     # Build Docker image
│   ├── docker-run.sh       # Run Docker container
│   └── deploy-k8s.sh       # Deploy to Kubernetes
│
├── CMakeLists.txt           # CMake build configuration
├── Dockerfile               # Docker image definition
├── docker-compose.yml       # Docker Compose configuration
├── .dockerignore           # Docker ignore rules
├── .gitignore              # Git ignore rules
├── requirements.txt         # Python version (legacy)
├── zork.py                 # Python version (legacy)
└── README.md               # This file
```

### File Count

The project consists of **30+ files** organized into:
- 9 header files (.h)
- 9 implementation files (.cpp)
- 3 JSON data files
- 3 Kubernetes manifests
- 5 shell scripts
- 3 Docker-related files
- 3 CMake/build files
- Various documentation and configuration files

---

## Architecture

### Core Components

**Game Engine**
- `Game` class orchestrates all game logic
- Manages world state, scoring, and game flow
- Coordinates between player, rooms, and commands

**Command System**
- `CommandParser` processes user input
- Supports command aliases and shortcuts
- Routes commands to appropriate handlers
- Returns structured results

**World Model**
- `Room` represents locations with exits and items
- Graph-based room connectivity
- Dynamic state (visited, lit, locked)
- Item management per room

**Player System**
- `Player` tracks character state and inventory
- Movement and interaction capabilities
- Combat statistics (health, attack, defense)
- Weight-based inventory management

**Item System**
- `Item` base class with specialized types
- Properties: weight, damage, defense, value
- Type-specific behaviors (weapons, keys, consumables)
- Use() method for item-specific actions

**Combat System**
- `Enemy` class with AI behavior
- Turn-based combat mechanics
- Damage calculation with defense
- Experience and reward system

**Utilities**
- `Utils` namespace with helper functions
- String manipulation (toLower, trim, split)
- File I/O operations
- Random number generation
- ANSI color support

### Design Patterns

**Command Pattern:** Used in command parsing and execution
**State Pattern:** Room states (lit/dark, locked/unlocked)
**Smart Pointers:** Memory safety with shared_ptr/unique_ptr
**RAII:** Resource management throughout
**Dependency Injection:** Game class receives dependencies

### Data Flow

```
User Input → CommandParser → Command Handler → Game Logic → State Update → Display Output
```

---

## Development

### Code Style

- C++17 standard
- CamelCase for class names
- camelCase for methods
- snake_case_ for private members
- UPPER_CASE for constants
- Include guards in all headers

### Adding New Features

**New Command:**
1. Add handler method in `CommandParser`
2. Update `setupAliases()` for shortcuts
3. Update `parse()` method routing
4. Update help text

**New Item:**
1. Define in `data/items.json`
2. Add creation in `Game::createItems()`
3. Implement special behavior in `Item::use()`

**New Room:**
1. Define in `data/rooms.json`
2. Add creation in `Game::createRooms()`
3. Connect exits in `Game::connectRooms()`

**New Enemy:**
1. Define in `data/enemies.json`
2. Implement AI in `Enemy::getAction()`
3. Add combat encounter logic

### Building Tests

```bash
cd build
cmake -DBUILD_TESTS=ON ..
make
ctest
```

### Debugging

**Debug build:**
```bash
./scripts/build.sh --debug
gdb ./build/zork
```

**With sanitizers:**
```bash
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS="-fsanitize=address" ..
make
./zork
```

---

## Required Enhancements

The following features are structured but need full implementation:

### 1. Complete Item Usage System

**Current State:** Items can be collected but usage is limited
**Requirements:**
- Implement context-aware item usage (use key on door, use lamp to light rooms)
- Item combination system (rope + hook = grappling hook)
- State changes based on usage (doors unlock, rooms light up)
- Puzzle mechanics requiring specific item combinations

**Files:** `src/Item.cpp`, `src/Command.cpp` (handleUse method)
**Priority:** High

### 2. Full Combat System Implementation

**Current State:** Enemy and combat classes exist but full turn-based system incomplete
**Requirements:**
- Complete turn-based combat flow
- Enemy AI decision making (attack/defend/flee based on health)
- Equipment system affecting combat stats
- Item usage during combat
- Experience and leveling system
- Multiple enemy types with varied behaviors

**Files:** `src/Enemy.cpp`, `src/Game.cpp` (combat methods), `src/Command.cpp`
**Priority:** High

### 3. Save/Load Game Functionality

**Current State:** SaveManager class exists but serialization not complete
**Requirements:**
- Full game state serialization (player position, inventory, room states, score)
- JSON-based save format for readability
- Multiple save slots support
- Auto-save feature to prevent progress loss
- Error handling for corrupted saves
- Save file versioning for compatibility

**Files:** `src/SaveManager.cpp`, `src/Game.cpp` (saveGame/loadGame methods)
**Priority:** Medium

### 4. JSON-Based World Loading

**Current State:** JSON files exist but are not loaded dynamically
**Requirements:**
- Parse rooms.json and create rooms dynamically
- Parse items.json and instantiate items from data
- Parse enemies.json for enemy definitions
- Support for modding through custom JSON files
- Validation and error handling for JSON data
- Hot-reload capability for development

**Files:** `src/Game.cpp` (setupWorld methods), new JSON parser utility
**Priority:** Medium

### 5. Advanced Inventory Weight System

**Current State:** Basic weight system implemented
**Requirements:**
- Item-specific weight affecting movement speed
- Strength-based carry capacity
- Penalties for over-encumbrance
- Container items (bags, backpacks) increasing capacity
- Weight distribution mechanics

**Files:** `src/Player.cpp`, `include/Player.h`
**Priority:** Low

### 6. Comprehensive Scoring System

**Current State:** Basic scoring for actions
**Requirements:**
- Achievement-based scoring (solve puzzles, defeat enemies, discover secrets)
- Milestone tracking with percentage completion
- Score breakdown by category
- High score persistence across sessions
- Ranking system with titles (Novice, Expert, Master)
- Negative scoring for deaths or failures

**Files:** `src/Game.cpp`, new Achievement system
**Priority:** Low

### 7. Complex Puzzle System

**Current State:** Basic room navigation
**Requirements:**
- Multi-step puzzles requiring item combinations
- Logic puzzles (riddles, pattern matching)
- Environmental puzzles (push blocks, pour liquids)
- Hidden rooms and secret passages
- Timed puzzles with consequences
- Puzzle hints system

**Files:** New puzzle system classes, `src/Game.cpp`
**Priority:** Medium

### 8. NPC and Dialogue System

**Current State:** Only hostile enemies exist
**Requirements:**
- Friendly NPCs with dialogue trees
- Quest-giving NPCs
- Trading system
- Reputation system affecting NPC interactions
- Multiple dialogue branches based on player choices
- NPC movement and schedules

**Files:** New NPC classes, dialogue system
**Priority:** Low

---

## Technical Notes

### Memory Management
- All dynamic objects use smart pointers (shared_ptr, unique_ptr)
- No manual memory management or raw pointers
- RAII principles throughout codebase

### Thread Safety
- Current implementation is single-threaded
- Future multiplayer would require thread-safe state management

### Performance
- Efficient room graph with O(1) navigation
- Hash-based command lookup
- Minimal string copying

### Cross-Platform
- Tested on Linux, macOS, and Windows
- Uses standard C++17 only (no platform-specific code)
- ANSI colors with fallback for terminals without support

---

## Troubleshooting

### Build Errors

**CMake version too old:**
```bash
# Update CMake
brew install cmake  # macOS
sudo apt install cmake  # Ubuntu
```

**Compiler not found:**
```bash
# Install compiler
sudo apt install build-essential  # Ubuntu
xcode-select --install  # macOS
```

**Linking errors:**
Ensure you're using C++17:
```bash
cmake -DCMAKE_CXX_STANDARD=17 ..
```

### Docker Issues

**Image won't build:**
```bash
# Clean build
docker-compose down
docker system prune -a
./scripts/docker-build.sh --no-cache
```

**Container exits immediately:**
Ensure stdin and tty are enabled:
```bash
docker run -it zork:latest
```

### Kubernetes Issues

**Pod not starting:**
```bash
kubectl describe pod <pod-name>
kubectl logs <pod-name>
```

**Persistent volume issues:**
```bash
kubectl get pv,pvc
kubectl describe pvc zork-saves-pvc
```

---

## Contributing

Contributions are welcome! Areas that need work:

1. Complete the TODO items in source code
2. Implement the required enhancements listed above
3. Add more rooms, items, and puzzles
4. Improve AI behavior for enemies
5. Add unit tests and integration tests
6. Optimize performance
7. Improve documentation

### Development Workflow

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly
5. Submit a pull request

---

## License

This project is provided as-is for educational and entertainment purposes.

---

## Acknowledgments

Inspired by the original Zork series created by Infocom in the late 1970s and early 1980s.

---

## Contact & Support

For questions, issues, or suggestions, please open an issue in the repository.

**Happy adventuring!** 🗺️⚔️
