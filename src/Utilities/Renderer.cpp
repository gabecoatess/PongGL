#include "Utilities/Renderer.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void Renderer::RenderScene() const
{
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(mainShader);

    PassShaderData();

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

void Renderer::InitializeMatrices()
{
    viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));
    projectionMatrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
}

void Renderer::InitializeShaders(const std::string& primaryVertexShaderPath, const std::string& primaryFragmentShaderPath)
{
    mainShader = LoadShader(primaryVertexShaderPath, primaryFragmentShaderPath);

    // glUseProgram(mainShader);
    transformLocation = glGetUniformLocation(mainShader, "transform");
    // glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(trans));
}

void Renderer::PassShaderData() const
{
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::rotate(modelMatrix, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix * viewMatrix * modelMatrix));
}
