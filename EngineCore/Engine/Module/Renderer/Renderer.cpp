#include "pch.h"
import Renderer;
import RenderContext;
import DX;
import EngineCore;
import Mesh;
import Agent;
import Transform;
import ShaderArchive;

namespace F
{
    Renderer::Renderer() :
        shader(ShaderArchive::Get().Fetch<Shader>("DefaultShader")), 
        mesh(nullptr)
    {
        
    }

    void Renderer::Update(float dt)
    {

    }
    void Renderer::Render(ID3D11DeviceContext* context)
	{
        DX& dx = DX::Get();
        
        Transform* transform = agent->GetModule<Transform>();
        XMMATRIX model = transform->GetMatrix();
        XMMATRIX view = EngineCore::GetCameraMatrix();
        XMMATRIX proj = XMMatrixIdentity();
        XMMATRIX mvp = model * view * proj;

        CBuffer0 cb0;
        XMStoreFloat4x4(&cb0.MVP, XMMatrixTranspose(mvp));
        dx.cBuffer0->UpdateBuffer(context, cb0);
        dx.cBuffer0->Bind(context);

        mesh->Bind(context);
        shader->Bind(context);

        context->Draw(mesh->GetVertexCount(), 0);
		//ctx->Draw();
	}
}