#include <fstream>
#include <iostream>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

    // Start with triangle
    float points[] = {
        0.0f,  0.5f,  0.0f, // x,y,z of first point.
        0.5f, -0.5f,  0.0f, // x,y,z of second point.
       -0.5f, -0.5f,  0.0f  // x,y,z of third point.
     };

    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Define shaders
    const GLuint mainShader = LoadShader("../vertShader.glsl", "../fragShader.glsl");

    // Loop
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(mainShader);
        glBindVertexArray(vao);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    // Terminate
    glfwTerminate();

    return 0;
}
