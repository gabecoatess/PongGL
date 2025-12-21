#ifndef SHADERREADER_H
#define SHADERREADER_H

#include <string>
#include <glad/glad.h>

GLuint LoadShader(std::string vertexPath, std::string fragPath);
GLuint CreateShaderFromSource(int shaderType, const char* shaderSource);

#endif //SHADERREADER_H
