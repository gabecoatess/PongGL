#include "Utilities/Application.hpp"

#include <iostream>
#include <glad/glad.h>

void GlfwErrorCallback(int errorNum, const char* errorDesc)
{
    std::cerr << "[" << errorNum << "] " << errorDesc << '\n';
}

void Application::Preload()
{
    std::cout << "Preload started...\n";

    glfwSetErrorCallback(GlfwErrorCallback);
    preloadSuccess = glfwInit();

    if (!preloadSuccess)
    {
        std::cerr << "Unable to preload application! There was an issue initializing GLFW.\n";
    }

    primaryMonitor = glfwGetPrimaryMonitor();
    videoMode = glfwGetVideoMode(primaryMonitor);

    std::cout << "Preload complete\n";
    std::cout << "[Primary Monitor: " << glfwGetMonitorName(primaryMonitor) << "]\n";
}

bool Application::Preloaded() const
{
    return preloadSuccess;
}

bool Application::Started() const
{
    return startSuccess;
}

void Application::Start()
{
    std::cout << "Application start requested...\n";

    // Configurables
    glfwWindowHint(GLFW_RESIZABLE, windowResizable);
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, openGLMajor);
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, openGLMinor);

    // Defaults (no compromise)
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

    if (windowPositionX == -1)
    {
        auto midPointX = videoMode->width * 0.5;
        auto windowMidPointX = windowWidth * 0.5;
        auto monitorCenterX = midPointX - windowMidPointX;

        glfwWindowHint(GLFW_POSITION_X, monitorCenterX);
    }
    else
    {
        glfwWindowHint(GLFW_POSITION_X, windowPositionX);
    }

    if (windowPositionY == -1)
    {
        auto midPointY = videoMode->height * 0.5;
        auto windowMidPointY = windowHeight * 0.5;
        auto monitorCenterY = midPointY - windowMidPointY;

        glfwWindowHint(GLFW_POSITION_Y, monitorCenterY);
    }
    else
    {
        glfwWindowHint(GLFW_POSITION_Y, windowPositionY);
    }

    primaryWindow = glfwCreateWindow(windowWidth, windowHeight, applicationTitle.c_str(), nullptr, nullptr);
    if (!primaryWindow)
    {
        std::cerr << "An unknown error occured when trying to create a window!\n";

        startSuccess = false;
        glfwTerminate();
    }

    glfwMakeContextCurrent(primaryWindow);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    startSuccess = true;
    std::cout << "Ready!\n";
}

void Application::DefineApplicationTitle(const std::string title)
{
    applicationTitle = title;
}


void Application::DefineWindowResolution(const int width, const int height)
{
    windowWidth = width;
    windowHeight = height;
}

void Application::DefineWindowResizable(const bool value)
{
    windowResizable = value;
}

void Application::DefineWindowPosition(const int x, const int y)
{
    windowPositionX = x;
    windowPositionY = y;
}

void Application::DefineOpenGLVersion(const int major, const int minor)
{
    openGLMajor = major;
    openGLMinor = minor;
}

GLFWwindow* Application::GetActiveWindow() const
{
    return primaryWindow;
}

bool Application::Active()
{
    return !glfwWindowShouldClose(primaryWindow);
}
