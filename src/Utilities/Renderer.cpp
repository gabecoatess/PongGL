#include "Utilities/Renderer.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

void Renderer::InitializeShaders(const std::string& primaryVertexShaderPath, const std::string& primaryFragmentShaderPath)
{
    mainShader = LoadShader(primaryVertexShaderPath, primaryFragmentShaderPath);

    // glm::mat4 trans = glm::mat4(1.0f);
    // trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
    // trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

    // glUseProgram(mainShader);
    transformLocation = glGetUniformLocation(mainShader, "transform");
    // glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(trans));
}

void Renderer::PassShaderData() const
{

}
