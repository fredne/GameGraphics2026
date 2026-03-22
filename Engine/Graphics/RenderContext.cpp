#include "pch.h"
#include "RenderContext.h"
#include "RenderTarget.h"
#include "Viewport.h"

namespace F
{
	RenderContext::RenderContext(ID3D11DeviceContext* context) :
		mainContext(context)
	{

	}
	RenderContext::~RenderContext()
	{
		if (mainContext) mainContext->Release();
	}

	void RenderContext::Draw(int count)
	{
		Clear();
		renderTarget->Bind(mainContext);
		//mainContext->Draw(count, 0);
	}
	void RenderContext::Clear() { mainContext->ClearRenderTargetView(renderTarget->GetRTView(), clearColor.GetData()); }

	ID3D11DeviceContext* RenderContext::GetMainContext() { return mainContext; }
	RenderTarget* RenderContext::CurrentRenderTarget() { return renderTarget; }
	void RenderContext::SetRenderTarget(RenderTarget* rt) { renderTarget = rt; }
	void RenderContext::SetClearColor(Color color) { clearColor = color; }

}
