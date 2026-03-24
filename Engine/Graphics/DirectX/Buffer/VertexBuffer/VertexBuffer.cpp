#include "pch.h"
import VertexBuffer;
#include "DX.h"

namespace F
{
    VertexBuffer::VertexBuffer(std::vector<Vertex>& vertices) : vertices(vertices)
    {
        vertexCount = vertices.size();
        bd = { vertexCount * (UINT)sizeof(Vertex) , D3D11_USAGE_DEFAULT, D3D11_BIND_VERTEX_BUFFER, 0, 0, 0 };
        vData = { vertices.data(), 0, 0 };
        DX::Get().device->CreateBuffer(&bd, &vData, &buffer);
        stride = sizeof(Vertex);
        offset = 0;
    }

    VertexBuffer::~VertexBuffer()
    {

    }

    void VertexBuffer::Release()
    {
        //if (buffer)
        //{
        //    buffer->Release();
        //    buffer = nullptr;
        //}
    }

    void VertexBuffer::Bind(ID3D11DeviceContext* context)
    {
        context->IASetVertexBuffers(0, 1, buffer.GetAddressOf(), &stride, &offset);
    }


}
