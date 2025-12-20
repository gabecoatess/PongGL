# PongGL

A simple Pong (1972) clone written in C++ using OpenGL.

## Description

The purpose of this project is to get the fundamentals down of OpenGL and get
basic abstractions written for future OpenGL projects.

## Getting Started

### Dependencies

**System**
* Windows 10/11 (primary)
* macOS / Linux (not actively tested)
* CMake
* OpenGL 4.1 Core support

**Bundled (downloaded locally)**
* GLFW 3.4
* GLAD (OpenGL 4.1 Core)

### Third-Party Setup

1. Download GLAD archive via the generator on [V1 GLAD generator](https://glad.dav1d.de/)
     - Language: C/C++
    - Specification: OpenGL
    - API/gl: Version 4.1
    - Profile: Core
2. Create a new directory called `external` and extract the GLAD archive into 
this folder
   - Rename the GLAD folder to `glad` if necessary
3. Download GLFW **source** archive via the [official GLFW website](https://www.glfw.org/download.html)
    - Ensure you are using version **3.4** which was released on **February 23, 2024**.
4. Extract the GLFW source archive into the `external` folder
    - Rename the GLFW source folder to `glfw-3.4` if necessary
5. Build GLFW
    - GLFW is built from source so it can be linked directly into the project
      without relying on system-installed binaries.
    ```sh
   cd .\external\glfw-3.4
   cmake -S . -B build
   cd .\build\
   cmake --build .
   ```
   
### Building (CMake)

_To be executed from the root directory_
```sh
cmake -S . -B build
cmake --build build
```

#### Optional (Ninja, recommended)

```sh
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

### Executing program

_To be executed from the root directory_
> Executable output paths depend on the CMake generator used.

```sh
# Ninja / Makefiles
./build/PongGL

# Visual Studio
.\build\Debug\PongGL.exe
```

## Project Structure

```s
PongGL/
├─ main.cpp
├─ src/
├─ external/
├─ CMakeLists.txt
├─ LICENSE
└─ README.md
```

## Authors

[@gabecoatess](https://gabecoatess.com)

## License

This project is licensed under the MIT License - see the LICENSE file for details