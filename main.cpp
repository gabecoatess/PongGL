#include <fstream>
#include <iostream>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "external/rapidobj/rapidobj.h"
#include "Utilities/Application.hpp"
#include "Utilities/Model.hpp"
#include "Utilities/Renderer.hpp"
#include "Utilities/ShaderReader.h"



int main()
{
    Application app;
    if (!app.Preloaded()) return -1;

    app.DefineApplicationTitle("PongGL");
    app.DefineOpenGLVersion(4, 1);

    app.Start();
    if (!app.Started()) return -1;

    // Create the renderer
    Renderer renderer(app);

    // Load meshes into renderer
    renderer.AddModel("../assets/models/pong_title.obj");
    renderer.AddModel("../assets/models/triangle.obj");

    while (app.Active())
    {
        renderer.RenderScene();
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
