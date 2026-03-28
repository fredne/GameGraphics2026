#include "pch.h"
import RenderTarget;
import DX;
import Viewport;

namespace F
{
	RenderTarget::RenderTarget(D3D11_VIEWPORT dVp)
	{
		viewport = new Viewport(dVp);
		ComPtr<ID3D11Texture2D> backBuffer = nullptr;
		DX::Get().swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
		DX::Get().device->CreateRenderTargetView(backBuffer.Get(), nullptr, dxRTV.GetAddressOf());

	}

	RenderTarget::~RenderTarget()
	{
		if (viewport)
		{
			delete viewport;
			viewport = nullptr;
		}
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

	const ID3D11RenderTargetView* RenderTarget::GetRTV() { return dxRTV.Get(); }
	const ID3D11ShaderResourceView* RenderTarget::GetSRV() { return dxSRV.Get(); }

	void RenderTarget::SetViewport(Viewport* vp)
	{
		if (viewport) delete viewport;
		viewport = vp;

	}

	void RenderTarget::AddDxViewPort(float top, float left, float width, float height, float minDepth, float maxDepth)
		{ viewport->AddViewPort(top, left, width, height, minDepth, maxDepth); }
	void RenderTarget::AddDxViewPort(D3D11_VIEWPORT dxViewport)
		{ viewport->AddViewPort(dxViewport); }

	Viewport* RenderTarget::GetViewport() { return viewport; }



}