#include "pch.h"
import RenderTarget;
#include "DX.h"
#include "Viewport.h"
#include "RenderContext.h"

namespace F
{
	RenderTarget::RenderTarget(D3D11_VIEWPORT dVp)
	{
		DX::Get().CreateRenderTargetView(this);
		viewport = new Viewport(dVp);

	}

	RenderTarget::~RenderTarget()
	{
		if (viewport)
		{
			delete viewport;
			viewport = nullptr;
		}
		//if (renderTargetView)
		//{
		//	renderTargetView->Release();
		//	renderTargetView = nullptr;
		//}


	}

	void RenderTarget::Bind(ID3D11DeviceContext* context)
	{
		context->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), nullptr);
		context->RSSetViewports(viewport->GetCount(), viewport->GetData());
	}


	void RenderTarget::SetViewport(Viewport* vp)
	{
		if (viewport) delete viewport;
		viewport = vp;

	}

	ComPtr<ID3D11RenderTargetView>& RenderTarget::GetRTView() { return renderTargetView; }
	const ID3D11RenderTargetView* RenderTarget::GetRTViewRaw() { return renderTargetView.Get(); }

	void RenderTarget::AddDxViewPort(float top, float left, float width, float height, float minDepth, float maxDepth)
		{ viewport->AddViewPort(top, left, width, height, minDepth, maxDepth); }
	void RenderTarget::AddDxViewPort(D3D11_VIEWPORT dxViewport)
		{ viewport->AddViewPort(dxViewport); }

	Viewport* RenderTarget::GetViewport() { return viewport; }

}