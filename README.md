# OpenGL Learning Repository

This repository is a personal space to track my progress learning **OpenGL** with C++, vcpckg and CMake.  

## Current Progress

- If you pull, build, and run the project as-is, you'll see a **textured pyramid with basic lighting**.  
- The code demonstrates:
  - 2 Shaders, a default one and a light one
  - Using vertices and indices for both lighting and models
  - Textures
  - Basic lighting (diffuse + ambient)
  - VBO, EBO and VAO classes
  - Camera class allows moving and rotating in window 

## Upcoming

New features or experiments will live in separate branches or folders, currently in progress:
- Specular maps
- Normal maps
- Advanced lighting
- ....

The `main` branch will remain a **stable base** — always showing the simple pyramid with texture and lighting.

## Building

### Prerequisites
1. C++ compiler (like MSVC on Windows, or g++/clang on Linux/macOS)
2. CMake (for generating build files)
3. VSCode (recommended)
   1. C++ extension (ms-vscode.cpptools)
   2. CMake Tools extension (ms-vscode.cmake-tools)

### How-To
1. git clone <repo-url>
3. Open the folder using VSCode
4. Open a terminal in VSCode
5. run cmake --build build
6. .\build\debug\openGL.exe

These are enough to build and run the project as described. Other IDEs may work, but VSCode with these extensions is the easiest way to get started.

## Camera Controls
1. Move with W, S, D & A
2. Use Space and Left Control to move up and down
3. Hold Left Shift to move camera faster
4. Use Right Mouse Click to rotate 

## Photos
1. main
<img width="768" height="707" alt="image" src="https://github.com/user-attachments/assets/ed6093fc-47b2-4943-9f91-a3d3d8b48985" />
