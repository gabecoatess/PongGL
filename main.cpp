#include <fstream>
#include <iostream>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "external/rapidobj/rapidobj.h"
#include "Utilities/Model.hpp"
#include "Utilities/ShaderReader.h"

void GlfwErrorCallback(int errorNum, const char* errorDesc)
{
    std::cerr << "[" << errorNum << "] " << errorDesc << '\n';
}

int main()
{
    // Set GLFW error callback
    glfwSetErrorCallback(GlfwErrorCallback);

    // Initialize GLFW
    if (!glfwInit())
    {
        return -1;
    }

    // Get primary monitor info
    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);

    std::cout << "(" << videoMode->width << ", " << videoMode->height << ")\n";

    int windowWidth = 640;
    int windowHeight = 480;

    auto midPointX = videoMode->width * 0.5;
    auto midPointY = videoMode->height * 0.5;

    auto windowMidPointX = windowWidth * 0.5;
    auto windowMidPointY = windowHeight * 0.5;

    auto monitorCenterX = midPointX - windowMidPointX;
    auto monitorCenterY = midPointY - windowMidPointY;

    // Set window hints
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_POSITION_X, monitorCenterX);
    glfwWindowHint(GLFW_POSITION_Y, monitorCenterY);
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

    // Initialize window
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Hello, World!", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Set OpenGL context
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    // Set window clear color to red
    glClearColor(0, 0, 0, 0);

    // Load triangle mesh data
    const Model triangleModel = Model("../assets/models/triangle.obj");

    // Create Vertex Array Object
    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, triangleModel.GetVertexBufferObject());
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Define shaders
    const GLuint mainShader = LoadShader(
        "../assets/shaders/vertShader.glsl",
        "../assets/shaders/fragShader.glsl");

    glPolygonMode(GL_FRONT, GL_FILL);
    // Loop
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(mainShader);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleModel.GetElementBufferObject());
        glDrawElements(GL_TRIANGLES, triangleModel.GetTotalIndices(), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    // Terminate
    glfwTerminate();

    return 0;
}
