#include "pch.h"
#include "VertexBuffer.h"
#include "DX.h"

namespace F
{
    VertexBuffer::VertexBuffer(std::vector<Vertex>& vertices) : vertices(vertices)
    {
        vertexCount = vertices.size();
        bd = { vertexCount * (UINT)sizeof(Vertex) , D3D11_USAGE_DEFAULT, D3D11_BIND_VERTEX_BUFFER, 0, 0, 0 };
        vData = { vertices.data(), 0, 0 };
        DX::device->CreateBuffer(&bd, &vData, &buffer);
        stride = sizeof(Vertex);
        offset = 0;
    }

    VertexBuffer::~VertexBuffer()
    {
        if (buffer)
        {
            buffer->Release();
            buffer = nullptr;
        }
    }

}
