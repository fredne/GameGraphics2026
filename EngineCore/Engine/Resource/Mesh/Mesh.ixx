#include "pch.h"
export module Mesh;
import VertexBuffer;

export namespace F
{
    class Transform;
    class Mesh
    {
    private:

    public:
        VertexBuffer* vBuffer;

        Mesh();
        ~Mesh();

        void Initialize(std::vector<Vertex>& vertexList);
        void Release();

        void Bind(ID3D11DeviceContext* context);

        uint32_t GetVertexCount() const { return vBuffer->vertexCount; }

    };

}

