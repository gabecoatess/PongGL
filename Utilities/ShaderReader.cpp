#include "ShaderReader.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <glad/glad.h>

GLuint LoadShader(std::string vertexPath, std::string fragPath)
{
    // Load vertex shader
    std::ifstream vertexShaderFile(vertexPath);
    if (!vertexShaderFile)
    {
        std::cerr << "Unable to open vertex shader!\n";
    }

    // Load fragment shader
    std::ifstream fragmentShaderFile(fragPath);
    if (!fragmentShaderFile)
    {
        std::cerr << "Unable to open fragment shader!\n";
    }

    // Load data into buffers
    std::ostringstream vertexFileStream;
    std::ostringstream fragmentFileStream;

    vertexFileStream << vertexShaderFile.rdbuf();
    fragmentFileStream << fragmentShaderFile.rdbuf();

    // Convert to source
    std::string vertexSource = vertexFileStream.str();
    std::string fragmentSource = fragmentFileStream.str();

    // Create shaders
    GLuint vertexShader = CreateShaderFromSource(GL_VERTEX_SHADER, vertexSource.c_str());
    GLuint fragmentShader = CreateShaderFromSource(GL_FRAGMENT_SHADER, fragmentSource.c_str());

    // Link into shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    return shaderProgram;
}

GLuint CreateShaderFromSource(const int shaderType, const char* shaderSource)
{
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    // Check for errors
    int compileSuccess;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileSuccess);

    if (!compileSuccess)
    {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Shader compilation failed with error: '" << infoLog << "'! Please fix errors before continuing\n";
    }

    return shader;
}