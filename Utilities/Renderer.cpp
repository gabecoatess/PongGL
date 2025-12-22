#include "Renderer.hpp"

#include "GLFW/glfw3.h"

void Renderer::RenderScene() const
{
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(mainShader);

    for (const auto& model : activeModels)
    {
        model.RenderModel();
    }

    glfwSwapBuffers(currentWindow);
}

void Renderer::AddModel(std::string modelPath)
{
    activeModels.emplace_back(modelPath);
}

void Renderer::CreateVertexArray()
{
    // Create the object
    glGenVertexArrays(1, &vertexArray);

    // Bind it to be active in the current OpenGL state
    glBindVertexArray(vertexArray);

    // Define the layout
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);
}