#ifndef RENDERER_HPP
#define RENDERER_HPP
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Application.hpp"
#include "Model.hpp"
#include "Utilities/ShaderReader.hpp"

class Renderer {
private:
    std::vector<Model> activeModels;
    GLuint vertexArray = 0;
    GLuint mainShader;
    Application& app;
    GLFWwindow* currentWindow;

    GLuint transformLocation;

    glm::mat4 viewMatrix = glm::mat4(1.0f);
    glm::mat4 projectionMatrix;

    const int maxModels = 1000;

public:
    Renderer(Application& _app) : app(_app)
    {
        activeModels.reserve(sizeof(Model) * maxModels);

        CreateVertexArray();

        glClearColor(0, 0, 0, 0);
        glPolygonMode(GL_FRONT, GL_FILL);

        InitializeMatrices();

        InitializeShaders(
            "./assets/shaders/vertShader.glsl",
            "./assets/shaders/fragShader.glsl");

        currentWindow = app.GetActiveWindow();
    }

    void InitializeMatrices();
    void RenderScene() const;
    void AddModel(std::string modelPath);

private:
    void CreateVertexArray();
    void InitializeShaders(const std::string& primaryVertexShaderPath, const std::string& primaryFragmentShaderPath );
    void PassShaderData() const;
};

#endif //RENDERER_HPP
