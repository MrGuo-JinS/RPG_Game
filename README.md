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
| Item System (Weapons, Armor, Consumables) | 🚧 In Progress |
| Player Stats & Progression | 🚧 In Progress |
| Inventory Management | 📋 Planned |
| Combat System | 📋 Planned |
| Quest System | 📋 Planned |
| Save / Load | 📋 Planned |
| Config-driven Data (JSON) | ✅ Implemented |

---

## 🗂️ Project Structure
```
VECTOR/
├── .vscode/ # VS Code configuration
├── assets/ # Game assets (textures, sounds, fonts)
├── build/ # Build output
│ └── vector.exe
├── config/ # JSON configuration files
│ ├── items/ # Item data by category
│ │ ├── armors/
│ │ ├── consumables/
│ │ ├── materials/
│ │ ├── tools/
│ │ └── weapons/
│ └── players/ # Player presets and stats
├── include/ # Header files (.hpp)
│ ├── Item.hpp
│ └── Logger.hpp
├── src/ # Source files (.cpp)
│ ├── Logger.cpp
│ └── main.cpp
├── third_party/ # External libraries
│ └── json.hpp # nlohmann/json
├── README.md
└── LICENSE
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
| [nlohmann/json](https://github.com/nlohmann/json) | v3.11.2+ | MIT License | JSON parsing for configuration files |

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
- [x] Build system setup
- [x] Logger system
- [x] JSON config loading
- [x] README & LICENSE

### Phase 2: Core Systems
- [x] Item base class
- [ ] Item categories (weapon / armor / consumable / material / tool)
- [ ] Item factory & loading from JSON
- [ ] Player class
- [ ] Character stats (HP, MP, ATK, DEF, etc.)

### Phase 3: Gameplay Mechanics
- [ ] Inventory system
- [ ] Equipment system
- [ ] Combat system
- [ ] Experience & leveling
- [ ] Skill system

### Phase 4: World & Content
- [ ] Map / Tile system
- [ ] NPC system
- [ ] Dialogue system
- [ ] Quest system
- [ ] Enemy AI

### Phase 5: User Interface
- [ ] Main menu
- [ ] HUD
- [ ] Inventory UI
- [ ] Dialogue UI
- [ ] Settings menu

### Phase 6: Polish & Release
- [ ] Save / Load
- [ ] Audio
- [ ] Balance tuning
- [ ] Bug fixes
- [ ] Release

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