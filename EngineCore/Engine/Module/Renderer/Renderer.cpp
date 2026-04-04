#include "pch.h"
import Renderer;
import RenderContext;
import DX;
import EngineCore;
import Mesh;
import Agent;
import Transform;
import ShaderArchive;
import Camera;

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
        XMMATRIX view = Camera::mainCamera->GetCameraMatrix();
        XMMATRIX proj = XMMatrixIdentity();
        XMMATRIX mvp = model * view * proj;

        XMStoreFloat4x4(&dx.cBuffer0->data.MVP, XMMatrixTranspose(mvp));
        dx.cBuffer0->BindVS(context, 0);

        dx.cBuffer3->data.color = color;
		dx.cBuffer3->BindPS(context, 3);

        mesh->Bind(context);
        shader->Bind(context);

        context->Draw(mesh->GetVertexCount(), 0);
		//ctx->Draw();
	}
}