cmake_minimum_required(VERSION 3.28)
project(PongGL C CXX)
set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

add_subdirectory(external/glfw-3.4)

#include_directories(SYSTEM external/glad-4.1/include)
add_library(glad STATIC external/glad-4.1/src/glad.c)
target_include_directories(glad PUBLIC external/glad-4.1/include)

add_executable(PongGL main.cpp)

target_link_libraries(PongGL PRIVATE glad OpenGL::GL glfw)