# VECTOR

> *In a world of corrupted data, one signal remains true.*

A sci-fi RPG built in C++.

---

## 📖 Story

The year is 2147. The **VECTOR** network — the digital backbone of human civilization — has collapsed. Data streams have turned hostile, corrupted by an unknown entity known only as **The Glitch**.

You are a **Signal Runner**, one of the few who can navigate the broken data streams. Armed with your wits, a modular weapon system, and the remnants of forgotten code, you must traverse the ruins of the digital world.

**Find the source. Rewrite the system. Restore the signal.**

---

## ✨ Features

| Feature | Status |
|---------|--------|
| Config-driven data (JSON) | ✅ Implemented |
| Item system (weapons, armor, consumables) | ✅ Implemented |
| Monster system with stats, resistances, loot, and AI | ✅ Implemented |
| Config manager with UUID and alias lookup | ✅ Implemented |
| Player system | 🚧 In Progress |
| Inventory and equipment systems | 📋 Planned |
| Combat system | 📋 Planned |
| Quest system | 📋 Planned |
| Save / load | 📋 Planned |

---

## 🗂️ Project Structure
```
RPG_Game/
├── .vscode/              # VS Code configuration
├── assets/               # Game assets
├── build/                # Build output directory
├── build.bat             # Windows build script
├── config/               # JSON configuration files
│   ├── item/             # Item definitions
│   ├── monster/          # Monster definitions
│   └── player/           # Player-related configs
├── include/              # Header files
│   ├── core/             # Core systems
│   ├── item/             # Item-related headers
│   ├── monster/          # Monster-related headers
│   └── utils/            # Utility headers
├── src/                  # Source files
│   ├── core/
│   ├── item/
│   ├── monster/
│   └── utils/
├── third_party/          # Third-party libraries
│   ├── glad/
│   ├── glfw/
│   ├── imgui/
│   └── json.hpp         # nlohmann/json
├── CMakeLists.txt
├── LICENSE
└── README.md
```


---

## 🔧 Build Instructions

### Prerequisites

- C++17 compatible compiler
- CMake (recommended) or your preferred build system

### Build with CMake

```bash
# Clone the repository
git clone <your-repo-url>
cd VECTOR

# Create build directory
mkdir build && cd build

# Generate build files
cmake ..

# Build
cmake --build . --config Release

# Run
./vector.exe          # Windows
./vector              # Linux / macOS
```

```bash
# Build Manually (g++)
g++ -std=c++17 -Iinclude src/*.cpp -o build/vector.exe
```

## 🎮 Controls

### Movement
| Key | Action |
|-----|--------|
| `W` / `↑` | Move Up |
| `S` / `↓` | Move Down |
| `A` / `←` | Move Left |
| `D` / `→` | Move Right |
| `Shift` | Sprint / Dash |

### Gameplay
| Key | Action |
|-----|--------|
| `Space` | Interact / Confirm |
| `E` | Use Item |
| `F` | Attack / Shoot |
| `R` | Reload / Recharge |
| `G` | Drop Item |
| `Tab` | Cycle Targets |

### Menu & UI
| Key | Action |
|-----|--------|
| `I` | Open / Close Inventory |
| `C` | Character Stats |
| `M` | Map |
| `Q` | Quest Log |
| `P` | Pause Game |
| `Esc` | Menu / Exit Prompt |

### Dialogue
| Key | Action |
|-----|--------|
| `Space` / `Enter` | Advance Dialogue |
| `1-9` | Dialogue Option Select |
| `Esc` | Skip Dialogue |

### Debug (Development Only)
| Key | Action |
|-----|--------|
| `F1` | Toggle Debug Overlay |
| `F2` | God Mode |
| `F3` | Spawn Test Enemy |
| `F5` | Quick Save |
| `F9` | Quick Load |

---

*Controls are subject to change during development.*

## 📦 Dependencies

| Library | Version | License | Purpose |
|---------|---------|---------|---------|
| [GLFW](https://www.glfw.org/) | 3.3+ | zlib/libpng | Window & Input Management |
| [GLAD](https://glad.dav1d.de/) | 0.1.36+ | MIT | OpenGL Extension Loader |
| [Dear ImGui](https://github.com/ocornut/imgui) | v1.90+ | MIT | Graphical User Interface |
| [nlohmann/json](https://github.com/nlohmann/json) | v3.11.2+ | MIT | JSON Configuration Parsing |

All dependencies are included in the `third_party/` directory with their respective licenses.

### Build Requirements

| Requirement | Version |
|-------------|---------|
| C++ Compiler | C++17 or higher |
| CMake (optional) | 3.10+ |

All dependencies are header-only. No additional linking required.

---

## 🗺️ Roadmap

### Phase 1: Foundation
- [x] Project directory structure
- [x] CMake-based build setup
- [x] JSON configuration manager
- [x] Item and monster data models
- [x] README & LICENSE

### Phase 2: Core Systems
- [x] Config-driven item loading
- [x] Monster stats, resistances, loot, and AI parsing
- [ ] Player character system
- [ ] Inventory and equipment systems
- [ ] Combat and damage logic

### Phase 3: Gameplay Mechanics
- [ ] Main gameplay loop
- [ ] Quest and progression systems
- [ ] Save / load support
- [ ] Skills and abilities

### Phase 4: World & Content
- [ ] Map and scene structure
- [ ] NPC interactions
- [ ] Dialogue system
- [ ] Enemy encounter design

### Phase 5: User Interface
- [ ] Main menu
- [ ] HUD and status display
- [ ] Inventory UI
- [ ] Dialogue UI
- [ ] Settings menu

### Phase 6: Polish & Release
- [ ] Audio and effects
- [ ] Balance tuning
- [ ] Bug fixes
- [ ] Release preparation

---

### Status Legend

| Icon | Meaning |
|------|---------|
| ✅ | Completed |
| 🚧 | In Progress |
| 📋 | Planned |

## 📄 License
This project is licensed under the MIT License — see the LICENSE file for details.

## 🤝 Contributing
This is a personal project, but suggestions and feedback are welcome!
+
+---
+
+*Follow the signal.*