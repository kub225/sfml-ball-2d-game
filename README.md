# sfml-ball-2d-game
2D physics maze game built with Modern C++ and SFML 3 featuring custom collisions and level management.



## Installation & Building

### Prerequisites

To build and run this game, you need:
- **IDE**: Visual Studio 2022 (or any C++17/C++20 compatible compiler).
- **Library**: [SFML 3.x](https://www.sfml-dev.org/download.php) (64-bit or 32-bit depending on your compiler settings).

---

### Step-by-Step Setup in Visual Studio

1. **Clone or Download the Repository**:
   Download the project files (`main.cpp`, assets `.png`, `.TTF`) into a single folder on your PC.

2. **Create a New Visual Studio Project**:
   - Open Visual Studio and create a new **C++ Console App**.
   - Set the C++ Language Standard to **C++17** or **C++20** (*Project Properties -> C/C++ -> Language -> C++ Language Standard*).

3. **Configure SFML 3 in Visual Studio**:
   - Open **Project Properties** (*Alt + F7*).
   - Go to **C/C++ -> General -> Additional Include Directories** and add the path to your SFML `include` folder (e.g., `C:\SFML-3.0.0\include`).
   - Go to **Linker -> General -> Additional Library Directories** and add the path to your SFML `lib` folder (e.g., `C:\SFML-3.0.0\lib`).
   - Go to **Linker -> Input -> Additional Dependencies** and add:
     - For **Release**: `sfml-graphics.lib`, `sfml-window.lib`, `sfml-system.lib`, `sfml-audio.lib`
     - For **Debug**: `sfml-graphics-d.lib`, `sfml-window-d.lib`, `sfml-system-d.lib`, `sfml-audio-d.lib`

4. **Add Game Files & Assets**:
   - Replace the default code in your main `.cpp` file with the game's C++ code.
   - Copy all dynamic link libraries (`sfml-graphics-3.dll`, `sfml-window-3.dll`, etc. from SFML's `bin` folder) into your project's build output directory (where the generated `.exe` resides, e.g., `x64/Debug` or root project folder).
   - Place all game assets (`.png` images and `ARIAL.TTF`) directly into the working directory of the project (where `.cpp` file is located).

5. **Build and Run**:
   Press **F5** or click **Start Debugging** to launch the game!
