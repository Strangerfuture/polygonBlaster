# 🕹️ polygonBlaster

A **retro-inspired twin-stick shooter** inspired by *Geometry Wars*.  
Built in **C++** with **SFML**, **ImGui**, and an **ECS design pattern** for clean, modular game architecture.  

---

## ✨ Features
- Fast-paced arcade action with a neon grid aesthetic  
- Smooth 2D rendering powered by **SFML**  
- **ImGui debug tools** for real-time tweaks  
- Modular **ECS design** for scalable gameplay systems  
- Particle effects & retro visuals  

---

## 🎮 Controls
- `WASD` – Move  
- `Mouse left` – Shoot in direction  
- `Mouse right` - Special Attack , yet to implement
- `P` – Pause
- `Esc` - Exit 

*(Controls may change as development continues.)*  

---

## 🔧 Tech Stack
- **C++20**  
- [SFML](https://www.sfml-dev.org/) – rendering, input, audio  
- [ImGui](https://github.com/ocornut/imgui) – debugging UI  
- **ECS architecture** – entity & system management  

---

## 🚀 Building From Source
### Prerequisites
- C++20 compatible compiler (GCC, Clang, or MSVC)  
- CMake (>=3.16)  
- SFML (>=2.6)  
- ImGui  

### Build Instructions
```bash
git clone https://github.com/Strangerfuture/polygonBlaster
cd polygonBlaster
mkdir build && cd build
cmake ..
make
./polygonBlaster
```
# Config Specification:

### Window W H FL FS

- This line declare that the SFML Window must be constructed with width W and height H,
    each of which will be integers, FL is frame Limit that the Window should be set to,
    FS will be an integer which specifies wheater to display the application in full-screen
    mode (1) or not (0).

### Font F S R G B

| Name      | Variable | Data type     |
|-----------|----------|---------------|
| Font File | F        | std::string   |
| Font Size | S        | int           |
| RGB Color | (R,G,B)  | int, int, int |

## Player Specification:

### Player SR CR S FR FG FB OR OG OB OT V

| Name              | Variable  | Data type     |
|-------------------|-----------|---------------|
|Shape Raduis       | SR        | int           |
| Collision Raduis  | CR        | int           |
| Speed             | S         | float         |
| Fill Color        | FR,FG,FB  | int, int, int |
| Outline Color     | OR,OR,OB  | int, int, int |
| Outline Thickness | OT        | int           |
| Shape Vertices    | V         | int           |

## Enemy Specification:

### Enemy SR CR SMIN SMAX OR OG OB OT VMIN VMAX L SI
| Name               | Variable   | Data type     |
|--------------------|------------|---------------|
| Shape Raduis       | SR         | int           |
| Collision Raduis   | CR         | int           |
| Min / Max Speed    | SMIN,SMAX  | float, float  |
| Outline Color      | OR,OG,OB   | int, int, int |
| Min / Max Vertices | VMIN,VMAX  | int, int      |
| Small Lifespan     | L          | int           |
| Spawn Interval     | SI         | int           |

## Bullet Specification:

### Bullet SR CR S FR FG FB OR OG OB OT V L 
| Name               | Variable   | Data type      |
|--------------------|------------|----------------|
| Shape Raduis       |  SR        |  int           |
| Collision Raduis   |  CR        |  int           |
| Speed              |  S         |  float         |
| Fill Color         |  FR,FG,FB  |  int, int, int |
| Outline Color      |  OR,OG,OB  |  int, int, int |
| Shape Vertices     |  V         |  int           |
| Lifespan           |  L         |  int           |

### TO generate Enemy randomly:
- Min / Max Speed       SMIN,SMAX   float, float
- Min / Max Vertices    VMIN,VMAX   int, int
 
```
 vec2f speed = {
    SMIN + rand() % (SMAX - SMIN + 1),
    SMIN + rand() % (SMAX - SMIN + 1),
 } 

float Vertices = VMIN + rand() % (VMAX - VMIN + 1);

vec2f Postion = {
    SR + rand() % ((wWidth - SR) - SR + 1),
    SR + rand() % ((wHeight- SR) - SR + 1),
}
```





