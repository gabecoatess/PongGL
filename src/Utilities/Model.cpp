#include "Utilities/Model.hpp"

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/euler_angles.hpp"

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

void Model::BindBuffers() const
{
    // Validate the buffers are generated
    if (!vertexBufferGenerated)
    {
        std::cerr << "Trying to bind a vertex buffer but it has not been generated!\n";
    }

    if (!elementBufferGenerated)
    {
        std::cerr << "Trying to bind a element buffer but it has not been generated!\n";
    }

    // Bind VBO first
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Bind EBO second
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
}

void Model::RenderModel()
{
    UpdateTransformMatrix();

    BindBuffers();
    glDrawElements(GL_TRIANGLES, GetTotalIndices(), GL_UNSIGNED_INT, 0);
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

            vertexBufferGenerated = true;

            break;

        case GL_ELEMENT_ARRAY_BUFFER:

            // Generate and set active
            glGenBuffers(1, &elementBuffer);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);

            // Populate active with data
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, GetTotalIndicesSize(), GetIndexData(), GL_STATIC_DRAW);

            elementBufferGenerated = true;

            break;

        default:
            std::cerr << "Failed to generate buffer. No buffer type was provided!\n";
    }
}

void Model::UpdateTransformMatrix()
{
    if (isScaleDirty)
    {
        transformMatrix = glm::scale(transformMatrix, scale);
        isScaleDirty = false;
    }

    if (isRotationDirty)
    {
        auto x = glm::yawPitchRoll(rotation.y, rotation.x, rotation.z);
        transformMatrix = transformMatrix * x;
        isRotationDirty = false;
    }

    if (isPositionDirty)
    {
        transformMatrix = glm::translate(transformMatrix, position);
        isPositionDirty = false;
    }
}

void Model::SetPosition(glm::vec3 newPosition)
{
    position = newPosition;
    isPositionDirty = true;
}

void Model::SetPosition(float x, float y, float z)
{
    SetPosition(glm::vec3(x, y, z));
}

void Model::SetPositionX(float x)
{
    SetPosition(x, position.y, position.z);
}

void Model::SetPositionY(float y)
{
    SetPosition(position.x, y, position.z);
}

void Model::SetPositionZ(float z)
{
    SetPosition(position.x, position.y, z);
}

void Model::SetRotation(glm::vec3 newRotation)
{
    rotation = newRotation;
    isRotationDirty = true;
}

void Model::SetRotation(float x, float y, float z)
{
    SetRotation(glm::vec3(x, y, z));
}

void Model::SetRotationX(float x)
{
    SetRotation(x, rotation.y, rotation.z);
}

void Model::SetRotationY(float y)
{
    SetRotation(rotation.x, y, rotation.z);
}

void Model::SetRotationZ(float z)
{
    SetRotation(rotation.x, rotation.y, z);
}

void Model::SetScale(glm::vec3 newScale)
{
    scale = newScale;
    isScaleDirty = true;
}

void Model::SetScale(float x, float y, float z)
{
    SetScale(glm::vec3(x, y, z));
}

void Model::SetScale(float value)
{
    SetScale(glm::vec3(value, value, value));
}

void Model::SetScaleX(float x)
{
    SetScale(x, scale.y, scale.z);
}

void Model::SetScaleY(float y)
{
    SetScale(scale.x, y, scale.z);
}

void Model::SetScaleZ(float z)
{
    SetScale(scale.x, scale.y, z);
}