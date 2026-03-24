#include "pch.h"
export module VertexBuffer;

export namespace F
{
    class VertexBuffer
    {
        std::vector<Vertex>& vertices;
        D3D11_BUFFER_DESC bd;
        D3D11_SUBRESOURCE_DATA vData;

    public:
        ComPtr<ID3D11Buffer> buffer;
        UINT stride = sizeof(Vertex);
        UINT offset = 0;
        UINT vertexCount = 0;

        VertexBuffer(std::vector<Vertex>& vertices);
        ~VertexBuffer();

        void Bind(ID3D11DeviceContext* context);
        void Release();

    };
}

