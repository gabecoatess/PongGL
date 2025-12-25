#ifndef MODEL_HPP
#define MODEL_HPP

#include <filesystem>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../external/rapidobj/rapidobj.h"

class Model {
public:
    const std::filesystem::path modelFile;

    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 scale = glm::vec3(0.0f, 0.0f, 0.0f);

    glm::mat4 transformMatrix = glm::mat4(1.0f);

private:
    std::vector<float> modelVertices;
    std::vector<unsigned int> modelIndices;

    GLuint vertexBuffer = 0;
    GLuint elementBuffer = 0;

    bool vertexBufferGenerated = false;
    bool elementBufferGenerated = false;
    bool isPositionDirty = false;
    bool isRotationDirty = false;
    bool isScaleDirty = false;

    rapidobj::Result meshData;

public:
    Model(std::string modelPath) : modelFile(modelPath)
    {
        // Load mesh data
        meshData = rapidobj::ParseFile(modelFile);

        // Input vertices
        for (int i = 0; i < meshData.attributes.positions.size(); i++)
        {
            modelVertices.push_back(meshData.attributes.positions[i]);
        }

        // Input indices
        for (int i = 0; i < meshData.shapes[0].mesh.indices.size(); i++)
        {
            modelIndices.push_back(meshData.shapes[0].mesh.indices[i].position_index);
        }

        // Prepare model
        GenerateBuffer(GL_ARRAY_BUFFER);
        GenerateBuffer(GL_ELEMENT_ARRAY_BUFFER);
    }

    int GetTotalVertices() const;
    int GetTotalIndices() const;

    int GetTotalVerticesSize() const;
    int GetTotalIndicesSize() const;

    const void* GetVertexData() const;
    const void* GetIndexData() const;

    GLuint GetVertexBufferObject() const;
    GLuint GetElementBufferObject() const;

    void BindBuffers() const;
    void RenderModel();
    void UpdateTransformMatrix();

    void Model::SetPosition(glm::vec3 newPosition);
    void Model::SetPosition(float x, float y, float z);
    void Model::SetPositionX(float x);
    void Model::SetPositionY(float y);
    void Model::SetPositionZ(float z);

    void Model::SetRotation(glm::vec3 newRotation);
    void Model::SetRotation(float x, float y, float z);
    void Model::SetRotationX(float x);
    void Model::SetRotationY(float y);
    void Model::SetRotationZ(float z);

    void Model::SetScale(glm::vec3 newScale);
    void Model::SetScale(float x, float y, float z);
    void Model::SetScale(float value);
    void Model::SetScaleX(float x);
    void Model::SetScaleY(float y);
    void Model::SetScaleZ(float z);

private:
    void GenerateBuffer(int bufferType);
};

#endif //MODEL_HPP
