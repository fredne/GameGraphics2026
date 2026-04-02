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
    Mesh::Mesh(std::vector<Vertex>& vertexList) :
        vBuffer(new VertexBuffer(vertexList))
    {

    }
    Mesh::~Mesh()
    {

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


    void Mesh::Update(float dt)
    {

    }

    void Mesh::Bind(ID3D11DeviceContext* context)
    {
        vBuffer->Bind(context);
    }

}
