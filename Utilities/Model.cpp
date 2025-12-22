#include "Model.hpp"

#include <iostream>

int Model::GetTotalVertices() const
{
    return modelVertices.size();
}

int Model::GetTotalIndices() const
{
    return modelIndices.size();
}

int Model::GetTotalVerticesSize() const
{
    return modelVertices.size() * sizeof(float);
}

int Model::GetTotalIndicesSize() const
{
    return modelIndices.size() * sizeof(int);
}

const void* Model::GetVertexData() const
{
    return modelVertices.data();
}

const void* Model::GetIndexData() const
{
    return modelIndices.data();
}

GLuint Model::GetVertexBufferObject() const
{
    return vertexBuffer;
}

GLuint Model::GetElementBufferObject() const
{
    return elementBuffer;
}

void Model::GenerateBuffer(int bufferType)
{
    switch(bufferType)
    {
        case GL_ARRAY_BUFFER:

            // Generate and set active
            glGenBuffers(1, &vertexBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

            // Populate active with data
            glBufferData(GL_ARRAY_BUFFER, GetTotalVerticesSize(), GetVertexData(), GL_STATIC_DRAW);

            break;

        case GL_ELEMENT_ARRAY_BUFFER:

            // Generate and set active
            glGenBuffers(1, &elementBuffer);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);

            // Populate active with data
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, GetTotalIndicesSize(), GetIndexData(), GL_STATIC_DRAW);

            break;

        default:
            std::cerr << "Failed to generate buffer. No buffer type was provided!\n";
    }
}
