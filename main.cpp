#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

    // Initialize window
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello, World!", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Set OpenGL context
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    // Set window clear color to red
    glClearColor(1, 0, 0, 0);

    // Loop
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    // Terminate
    glfwTerminate();

    return 0;
}
