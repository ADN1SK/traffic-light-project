# Interactive Traffic Light Simulator

A high-performance, cross-platform traffic light simulation built using C++ and the OpenGL Utility Toolkit (GLUT). This project demonstrates real-time state machine logic, 2D vector graphics rendering, and interactive event handling via keyboard and mouse inputs.

## 🚀 Features

- **Automated Cycling**: Intelligent state transitions based on millisecond-accurate timing.
- **Manual Override**: Real-time control via keyboard hotkeys.
- **Interactive UI**: Clickable light components using coordinate mapping and collision detection.
- **State Persistence**: Visual feedback for paused and active states.

## 🎮 Controls

### Keyboard Shortcuts

| Key       | Action                             |
| :-------- | :--------------------------------- |
| `R` / `r` | Manually switch to **RED**         |
| `Y` / `y` | Manually switch to **YELLOW**      |
| `G` / `g` | Manually switch to **GREEN**       |
| `S` / `s` | **Pause/Resume** automatic cycling |
| `ESC`     | Exit the application               |

### Mouse Interaction

- **Left Click**: Click directly on any of the light circles (Red, Yellow, or Green) to force a state change to that specific color.

## 🛠 Technical Specifications

### State Timing

The automatic sequence follows the logic: `Red` → `Green` → `Yellow` → `Red`.

| Light      | Duration (ms) | RGB Color (Active) |
| :--------- | :------------ | :----------------- |
| **Red**    | 3000ms        | `(1.0, 0.0, 0.0)`  |
| **Green**  | 3000ms        | `(0.0, 1.0, 0.0)`  |
| **Yellow** | 1000ms        | `(1.0, 1.0, 0.0)`  |

### Rendering Logic

- **Geometry**: Circles are rendered using `GL_TRIANGLE_FAN` with 100-segment precision for smooth edges.
- **Coordinates**: The simulation uses a normalized coordinate system spanning from `-1.0` to `1.0`.
- **Collision Detection**: Implements a standard Euclidean distance check: $(dx^2 + dy^2) \leq radius^2$.

## 📦 Installation & Build

### Prerequisites

Ensure you have the OpenGL and GLUT development libraries installed.

**Debian/Ubuntu:**

```bash
sudo apt-get install freeglut3-dev
```

### Compilation

Use the following command to compile the source code:

```bash
g++ "trafficlight.c++" -o traffic_light -lGL -lGLU -lglut
```

### Running the Program

```bash
./traffic_light
```
---
## 📂 Project Structure

```text
traffic-light-project/
├── trafficlight.c++    # Main source code
└── README.md           # Project documentation
```

---

_Developed as part of a software engineering learning path focusing on computer graphics and event-driven programming._

---



