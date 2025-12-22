#include "Model.hpp"

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
