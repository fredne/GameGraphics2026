#include "pch.h"
import RenderTarget;
import DX;
import Viewport;

namespace F
{
	RenderTarget::RenderTarget(D3D11_VIEWPORT dVp)
	{
		viewport = new Viewport(dVp);
		Create();

	}

	RenderTarget::~RenderTarget()
	{
		if (viewport)
		{
			delete viewport;
			viewport = nullptr;
		}
	}


	void RenderTarget::ResizeRenderTarget(D3D11_VIEWPORT dxVp)
	{
		Create();
		viewport->Resize(dxVp);
	}
	void RenderTarget::Create()
	{
		ComPtr<ID3D11Texture2D> buffer = nullptr;
		DX::Get().swapChain->GetBuffer(0, IID_PPV_ARGS(&buffer));
		DX::Get().device->CreateRenderTargetView(buffer.Get(), nullptr, &dxRTV);
	}
	void RenderTarget::Reset()
	{
		dxRTV.Reset(); dxSRV.Reset();
	}

	void RenderTarget::SetClearColor(Color color) { clearColor = color; }
	void RenderTarget::ClearColor(ID3D11DeviceContext* context)
	{
		context->ClearRenderTargetView(dxRTV.Get(), clearColor.GetData());
	}

	void RenderTarget::BindAsTarget(ID3D11DeviceContext* context, ID3D11DepthStencilView* dsv)
	{
		context->OMSetRenderTargets(1, dxRTV.GetAddressOf(), dsv);
		context->RSSetViewports(viewport->GetCount(), viewport->GetData());

	}
	void RenderTarget::BindAsResource(ID3D11DeviceContext* context, uint32_t slot)
	{
		context->PSSetShaderResources(slot, 1, dxSRV.GetAddressOf());
	}

	ID3D11RenderTargetView* RenderTarget::GetRTV() { return dxRTV.Get(); }
	ID3D11ShaderResourceView* RenderTarget::GetSRV() { return dxSRV.Get(); }

	void RenderTarget::SetViewport(Viewport* vp)
	{
		if (viewport) delete viewport;
		viewport = vp;

	}

	void RenderTarget::AddDxViewPort(float top, float left, float width, float height, float minDepth, float maxDepth)
		{ viewport->AddViewPort(top, left, width, height, minDepth, maxDepth); }
	void RenderTarget::AddDxViewPort(D3D11_VIEWPORT dxViewport)
		{ viewport->AddDxViewPort(dxViewport); }

	Viewport* RenderTarget::GetViewport() { return viewport; }

	Vector2<uint32_t> RenderTarget::GetCurrentRenderSize()
	{
		D3D11_VIEWPORT dxVp = viewport->GetDxViewPort(0);
		return { (uint32_t)dxVp.Width, (uint32_t)dxVp.Height };
	}

}