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
The `main` branch will remain a **stable base** — always showing the simple pyramid with texture and lighting, please switch branches to see progress
1. main:
   1. 2 Shaders, a default one and a light one
   2. Using vertices and indices for both lighting and models
   3. Textures
   4. Basic lighting (hard-coded ambient, specular, and diffuse lighting)
   5. VBO, EBO, and VAO classes
   6. Camera class allows moving and rotating in the window

<img width="800" height="800" alt="Screenshot 2025-08-21 193307" src="https://github.com/user-attachments/assets/639c58e3-852b-4b69-9323-90c12059fa08" />

1. specular-maps:
   1. Used two structs for better organization in the fragment shader
   2. Material struct contains shininess (float), diffuse and specular sampler2D (no longer vec3 or floats), and can be set from a image/texture/map
   4. Light struct contains vec3 for diffuse, specular, and ambient properties
   5. Able to sets light color that to tint objects

Diffuse Map
<img width="800" height="829" alt="Screenshot 2025-08-22 113248" src="https://github.com/user-attachments/assets/c1bca76b-d491-4399-adde-217e3469d6b1" />
Diffuse and Specular Maps
<img width="798" height="831" alt="Screenshot 2025-08-22 112808" src="https://github.com/user-attachments/assets/27d92b79-3191-49ca-994f-184821097df8" />
Maps + Light Color
<img width="799" height="829" alt="Screenshot 2025-08-22 115341" src="https://github.com/user-attachments/assets/8fe6cc47-9484-46dc-82e9-7961587df2c1" />
