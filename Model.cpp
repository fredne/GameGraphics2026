#include "pch.h"
#include "Model.h"
import VertexBuffer;
#include "DX.h"
#include "Keyboard/Keyboard.h"
import Engine;
import Transform;
import ConstantBuffer;

namespace F
{
    Model::Model() :
        transform(new Transform()), vBuffer(nullptr)
    {

    }
    Model::~Model()
    {

    }

    void Model::Release()
    {
        if (vBuffer)
        {
            vBuffer->Release();
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
        if (Keyboard::Get().aKey.IsPressed())
        {
            transform->position.x -= move;
            b = false;
        }
        if (Keyboard::Get().dKey.IsPressed())
        {
            transform->position.x += move;
            b = true;
        }
        if (Keyboard::Get().wKey.IsPressed())
        {
            transform->position.y += move;
        }
        if (Keyboard::Get().sKey.IsPressed())
        {
            transform->position.y -= move;
        }

    }

    void Model::Render(ID3D11DeviceContext* context)
    {
        DX& dx = DX::Get();
        XMMATRIX model = transform->GetMatrix();
        XMMATRIX view = Engine::GetCameraMatrix();
        XMMATRIX proj = XMMatrixIdentity();
        XMMATRIX mvp = model * view * proj;

        CBuffer0 cb0;
        XMStoreFloat4x4(&cb0.MVP, XMMatrixTranspose(mvp));
        dx.cBuffer0->UpdateBuffer(context, cb0);
        dx.cBuffer0->Bind(context);

        vBuffer->Bind(context);
        context->Draw(vBuffer->vertexCount, 0);
    }

}
