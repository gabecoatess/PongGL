cmake_minimum_required(VERSION 3.28)
project(PongGL C CXX)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 	0af55ccecd98d4e5a8d1fad7de25ba429d60e863
)
FetchContent_MakeAvailable(glm)

find_package(OpenGL REQUIRED)

add_subdirectory(external/glfw-3.4)

add_library(glad STATIC external/glad-4.1/src/glad.c)
target_include_directories(glad PUBLIC external/glad-4.1/include)

add_executable(PongGL main.cpp
        src/Utilities/ShaderReader.cpp
        src/Utilities/Model.cpp
        src/Utilities/Renderer.cpp
        src/Utilities/Application.cpp)

target_include_directories(PongGL PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(PongGL PRIVATE glad OpenGL::GL glfw glm::glm)

add_custom_command(TARGET PongGL POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_CURRENT_SOURCE_DIR}/assets
                   ${CMAKE_CURRENT_BINARY_DIR}/assets)