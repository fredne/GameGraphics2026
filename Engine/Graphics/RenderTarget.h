#pragma once

namespace F
{
	class Viewport;
	class RenderContext;
	class RenderTarget
	{
		ID3D11RenderTargetView* renderTargetView = nullptr;
		Viewport* viewport;

	public:
		RenderTarget(IDXGISwapChain* swapChain, D3D11_VIEWPORT dVp);
		~RenderTarget();

		void Bind(ID3D11DeviceContext* context);

		ID3D11RenderTargetView* GetRTView();
		
		void SetViewport(Viewport* vp);
		void AddDxViewPort(float top, float left, float width, float height, float minDepth, float maxDepth);
		void AddDxViewPort(D3D11_VIEWPORT dVp);
		Viewport* GetViewport();



	};

}

