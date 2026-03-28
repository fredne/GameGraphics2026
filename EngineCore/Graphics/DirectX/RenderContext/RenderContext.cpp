#include "pch.h"
import RenderContext;
import DX;
import EngineCore;
import Window;	

namespace F
{
	ID3D11DeviceContext* RenderContext::mainContext = nullptr;
	RenderContext::RenderContext(Vector2 size) :
		renderTarget(nullptr)
	{

	}

	RenderContext::~RenderContext()
	{
		if (renderTarget)
		{
			delete renderTarget;
			renderTarget = nullptr;
		}
	}

	ID3D11DeviceContext* RenderContext::GetMainContext() { return mainContext; }
	void RenderContext::SetMainContext(ID3D11DeviceContext* context) { mainContext = context; }

	RenderTarget* RenderContext::CurrentRenderTarget() { return renderTarget; }
	void RenderContext::SetRenderTarget(RenderTarget* rt) { renderTarget = rt; }

}
