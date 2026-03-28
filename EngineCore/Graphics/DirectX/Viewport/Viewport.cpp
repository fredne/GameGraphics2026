#include "pch.h"
import Viewport;

namespace F
{
	Viewport::Viewport(float top, float left, float width, float height, float minDepth, float maxDepth)
	{
		AddViewPort(top, left, width, height, minDepth, maxDepth);
	}

	Viewport::Viewport(D3D11_VIEWPORT dViewport)
	{
		AddViewPort(dViewport);
	}

	Viewport::~Viewport()
	{
	}

	void Viewport::AddViewPort(float top, float left, float width, float height, float minDepth, float maxDepth)
		{ viewportList.push_back({ top, left, width, height, minDepth, maxDepth }); }
	void Viewport::AddViewPort(D3D11_VIEWPORT dxViewport)
		{ viewportList.push_back(dxViewport); }

	D3D11_VIEWPORT* Viewport::GetData() { return viewportList.data(); }
	UINT Viewport::GetCount() { return viewportList.size(); }
}