#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "Utilities/Application.hpp"
#include "Utilities/Renderer.hpp"

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
    Model& pongTitleModel = renderer.AddModel("./assets/models/pong_title.obj");
    Model& triangleModel = renderer.AddModel("./assets/models/triangle.obj");

    // Set model transforms
    triangleModel.SetScale(0.3f);
    triangleModel.SetPositionX(-0.53f);
    triangleModel.SetPositionY(0.4f);

    while (app.Active())
    {
        triangleModel.SetRotationZ(pongTitleModel.rotation.z + 0.0005f);
        renderer.RenderScene();
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
