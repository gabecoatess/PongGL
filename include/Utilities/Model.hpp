#ifndef MODEL_HPP
#define MODEL_HPP

#include <filesystem>
#include <glad/glad.h>

#include "../external/rapidobj/rapidobj.h"

class Model {
public:
    const std::filesystem::path modelFile;

private:
    std::vector<float> modelVertices;
    std::vector<unsigned int> modelIndices;

    GLuint vertexBuffer = 0;
    GLuint elementBuffer = 0;

    bool vertexBufferGenerated = false;
    bool elementBufferGenerated = false;

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
    void RenderModel() const;

private:
    void GenerateBuffer(int bufferType);
};

#endif //MODEL_HPP
