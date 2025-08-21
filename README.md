# OpenGL Learning Repository

This repository is a personal space to track my progress learning **OpenGL** with C++, vcpckg and CMake.  

## Building

### Prerequisites
1. **C++ compiler** (like MSVC on Windows, or g++/clang on Linux/macOS)
2. **CMake** (for generating build files)
3. **VSCode** (recommended)
   1. C++ extension (ms-vscode.cpptools)
   2. CMake Tools extension (ms-vscode.cmake-tools)

These are enough to build and run the project as described. Other IDEs may work, but VSCode with these extensions is the easiest way to get started.

### Dependencies
- **GLFW** – window creation, input handling, OpenGL context
- **GLAD** – OpenGL function loader
- **GLM** – math library (vectors, matrices, transformations)
- **stb_image** – image loading for textures

### How-To
1. git clone <repo-url>
3. Open the folder using VSCode
4. Open a terminal in VSCode
5. run cmake --build build
6. .\build\debug\openGL.exe

## Camera Controls
1. Move with **W, S, D & A**
2. Use **Space and Left Control** to move up and down
3. Hold **Left Shift** to move camera faster
4. Use **Right Mouse Click** to rotate 

## Current Progress
1. main:
1.  2 Shaders, a default one and a light one
  2. Using vertices and indices for both lighting and models
  3. Textures
  4. Basic lighting (hard-coded ambient, specular, and diffuse lighting)
  5. VBO, EBO, and VAO classes
  6. Camera class allows moving and rotating in the window 

<img width="800" height="800" alt="Screenshot 2025-08-21 193307" src="https://github.com/user-attachments/assets/639c58e3-852b-4b69-9323-90c12059fa08" />

## Upcoming

New features or experiments will live in separate branches or folders, currently in progress:
- Specular and normal maps
- FBO Buffers
- ....

The `main` branch will remain a **stable base** — always showing the simple pyramid with texture and lighting.
