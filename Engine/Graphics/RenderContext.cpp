#include "pch.h"
#include "RenderContext.h"
import RenderTarget;
#include "Viewport.h"
#include "DX.h"
import Engine;
import Window;	

namespace F
{
	ID3D11DeviceContext* RenderContext::mainContext = nullptr;
	RenderContext::RenderContext() :
		renderTarget(nullptr)
	{
		Window* window = Engine::Get().GetWindow();
		Vector2 windowSize = window->GetWindowSize();

		D3D11_VIEWPORT viewPort = { 0, 0, windowSize.x, windowSize.y, 0.0, 0.1f };
		renderTarget = new RenderTarget(viewPort);
	}

	RenderContext::~RenderContext()
	{
		if (renderTarget)
		{
			delete renderTarget;
			renderTarget = nullptr;
		}
	}

	void RenderContext::Clear() 
	{ 
		mainContext->ClearRenderTargetView(renderTarget->GetRTView().Get(), clearColor.GetData());
	}
	void RenderContext::Bind()
	{
		renderTarget->Bind(mainContext);
	}
	void RenderContext::SwapChain()
	{
		//swapChain->Present(0, DXGI_PRESENT_ALLOW_TEARING);
		DX::Get().SwapChain();
	}

	ID3D11DeviceContext* RenderContext::GetMainContext() { return mainContext; }
	void RenderContext::SetMainContext(ID3D11DeviceContext* context) { mainContext = context; }

	RenderTarget* RenderContext::CurrentRenderTarget() { return renderTarget; }
	void RenderContext::SetRenderTarget(RenderTarget* rt) { renderTarget = rt; }
	void RenderContext::SetClearColor(Color color) { clearColor = color; }

}
