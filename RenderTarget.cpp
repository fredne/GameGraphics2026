#include "pch.h"
#include "RenderTarget.h"
#include "DX.h"
#include "Viewport.h"
#include "RenderContext.h"

namespace F
{
	RenderTarget::RenderTarget(IDXGISwapChain* swapChain, D3D11_VIEWPORT dVp)
	{
		ID3D11Texture2D* backBuffer = nullptr;
		swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
		DX::device->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);
		backBuffer->Release();
		viewport = new Viewport(dVp);
	}

	RenderTarget::~RenderTarget()
	{
		if (renderTargetView) renderTargetView->Release();
		if (viewport) delete viewport;

	}

	void RenderTarget::SetViewport(Viewport* vp)
	{
		if (viewport) delete viewport;
		viewport = vp;

	}
	void RenderTarget::Bind(ID3D11DeviceContext* context)
	{
		context->OMSetRenderTargets(1, &renderTargetView, nullptr);
		context->RSSetViewports(viewport->GetCount(), viewport->GetData());
	}

	ID3D11RenderTargetView* RenderTarget::GetRTView() { return renderTargetView; }

	void RenderTarget::AddDxViewPort(float top, float left, float width, float height, float minDepth, float maxDepth)
		{ viewport->AddViewPort(top, left, width, height, minDepth, maxDepth); }
	void RenderTarget::AddDxViewPort(D3D11_VIEWPORT dxViewport)
		{ viewport->AddViewPort(dxViewport); }

	Viewport* RenderTarget::GetViewport() { return viewport; }

}