#include "pch.h"
export module Viewport;

export namespace F
{
	class Viewport
	{
	private:
		std::vector<D3D11_VIEWPORT> viewportList;

	public:
		Viewport(float top, float left, float width, float height, float minDepth, float maxDepth);
		Viewport(D3D11_VIEWPORT dViewport);
		~Viewport();

		void Resize(D3D11_VIEWPORT dxViewport);
		void Clear();

		void AddViewPort(float top, float left, float width, float height, float minDepth, float maxDepth);
		void AddDxViewPort(D3D11_VIEWPORT dxViewport);

		D3D11_VIEWPORT* GetData() { return viewportList.data(); }
		D3D11_VIEWPORT GetDxViewPort(uint32_t index) { return viewportList[index]; }
		UINT GetCount() { return viewportList.size(); }

	};

}
