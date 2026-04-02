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

        Mesh(std::vector<Vertex>& vertexList);
        ~Mesh();

        void Release();

        void Update(float dt);

        void Bind(ID3D11DeviceContext* context);

        uint32_t GetVertexCount() { return vBuffer->vertexCount; }

    };

}

