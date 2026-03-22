#include "pch.h"
#include "Model.h"
#include "Transform/Transform.h"
#include "VertexBuffer.h"
#include "DX.h"

namespace F
{
    Model::Model() :
        transform(new Transform()), vBuffer(nullptr)
    {

    }
    Model::~Model()
    {
        if (vBuffer)
        {
            vBuffer->buffer->Release();
            delete vBuffer;
            vBuffer = nullptr;
        }

        if (transform)
        {
            delete transform;
            transform = nullptr;
        }
    }

    void Model::Update(float dt)
    {
        float move = speed * dt;
        if (GetAsyncKeyState('A') && 0x0001)
        {
            transform->position.x -= move;
        }
        if (GetAsyncKeyState('D') && 0x0001)
        {
            transform->position.x += move;
        }
        if (GetAsyncKeyState('W') && 0x0001)
        {
            transform->position.y += move;
        }
        if (GetAsyncKeyState('S') && 0x0001)
        {
            transform->position.y -= move;
        }

    }

    void Model::Render(ID3D11DeviceContext* context)
    {
        context->IASetVertexBuffers(0, 1, &vBuffer->buffer, &vBuffer->stride, &vBuffer->offset);
        XMStoreFloat4x4(&cb0.world, transform->GetMatrixInverse());
        context->UpdateSubresource(cBuffer0, 0, nullptr, &cb0, 0, 0);
        context->VSSetConstantBuffers(0, 1, &cBuffer0);
        context->Draw(vBuffer->vertexCount, 0);
    }

}
