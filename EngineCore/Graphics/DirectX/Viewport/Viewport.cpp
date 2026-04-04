#include "pch.h"
import Viewport;

namespace F
{
	Viewport::Viewport(float top, float left, float width, float height, float minDepth, float maxDepth)
	{
		AddViewPort(top, left, width, height, minDepth, maxDepth);
	}

	Viewport::Viewport(D3D11_VIEWPORT dxViewport)
	{
		AddDxViewPort(dxViewport);
	}

	Viewport::~Viewport()
	{
	}

	void Viewport::Resize(D3D11_VIEWPORT dxViewport)
	{
		Clear();
		AddDxViewPort(dxViewport);
	}

	void Viewport::Clear()
	{
		viewportList.clear();
	}

	void Viewport::AddViewPort(float top, float left, float width, float height, float minDepth, float maxDepth)
		{ viewportList.push_back({ top, left, width, height, minDepth, maxDepth }); }
	void Viewport::AddDxViewPort(D3D11_VIEWPORT dxViewport)
		{ viewportList.push_back(dxViewport); }

}