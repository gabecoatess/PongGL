#ifndef APPLICATION_HPP
#define APPLICATION_HPP
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Application {
public:
    std::string applicationTitle = "Hello, Application!";
    int windowWidth = 640;
    int windowHeight = 480;
    int windowPositionX = -1;
    int windowPositionY = -1;
    int openGLMajor = 3;
    int openGLMinor = 3;
    bool windowResizable = false;

private:
    GLFWwindow* primaryWindow;
    GLFWmonitor* primaryMonitor;
    bool preloadSuccess = false;
    bool startSuccess = false;
    const GLFWvidmode* videoMode;

public:
    Application()
    {
        Preload();
    }

    bool Preloaded() const;
    bool Started() const;
    void Start();

    void DefineApplicationTitle(std::string title);
    void DefineWindowResolution(int width, int height);
    void DefineWindowResizable(bool value);
    void DefineWindowPosition(int x, int y);
    void DefineOpenGLVersion(int major, int minor);

    GLFWwindow* GetActiveWindow() const;
    bool Active() ;

private:
    void Preload();
};

#endif //APPLICATION_HPP
