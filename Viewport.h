#pragma once

namespace F
{
	class Viewport
	{
	private:
		std::vector<D3D11_VIEWPORT> viewportList;

	public:
		Viewport(float top, float left, float width, float height, float minDepth, float maxDepth);
		Viewport(D3D11_VIEWPORT dViewport);
		~Viewport();
		
		void AddViewPort(float top, float left, float width, float height, float minDepth, float maxDepth);
		void AddViewPort(D3D11_VIEWPORT dxViewport);

		D3D11_VIEWPORT* GetData();
		UINT GetCount();
	};

}
