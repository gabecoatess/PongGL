#ifndef RENDERER_HPP
#define RENDERER_HPP
#include <vector>

#include "Model.hpp"
#include "ShaderReader.h"
#include "GLFW/glfw3.h"

class Renderer {
private:
    std::vector<Model> activeModels;
    GLuint vertexArray = 0;
    GLuint mainShader;
    GLFWwindow* currentWindow;

    const int maxModels = 1000;

public:
    Renderer(GLFWwindow* window) : currentWindow(window)
    {
        activeModels.reserve(sizeof(Model) * maxModels);

        CreateVertexArray();

        glClearColor(0, 0, 0, 0);
        glPolygonMode(GL_FRONT, GL_FILL);

        mainShader = LoadShader(
            "../assets/shaders/vertShader.glsl",
            "../assets/shaders/fragShader.glsl");
    }

    void RenderScene() const;
    void AddModel(std::string modelPath);

private:
    void CreateVertexArray();
};

#endif //RENDERER_HPP
