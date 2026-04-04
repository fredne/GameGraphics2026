#include "pch.h"
import Mesh;
import VertexBuffer;
import DX;
import Keyboard;
import EngineCore;
import Transform;
import ConstantBuffer;

namespace F
{
    Mesh::Mesh() :
        vBuffer(nullptr)
    {

    }
    Mesh::~Mesh()
    {
		Release();
    }

    void Mesh::Initialize(std::vector<Vertex>& vertexList)
    {
        vBuffer = new VertexBuffer(vertexList);
    }

    void Mesh::Release()
    {
        if (vBuffer)
        {
            vBuffer->Release();
            delete vBuffer;
            vBuffer = nullptr;
        }

    }

    void Mesh::Bind(ID3D11DeviceContext* context)
    {
        vBuffer->Bind(context);
    }

}
