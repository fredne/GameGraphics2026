#include "pch.h"
export module RenderTarget;

export namespace F
{
	class Viewport;
	class RenderContext;
	class RenderTarget
	{
		ComPtr<ID3D11RenderTargetView> renderTargetView;
		Viewport* viewport;

	public:
		RenderTarget(D3D11_VIEWPORT dVp);
		~RenderTarget();

		void Bind(ID3D11DeviceContext* context);

		ComPtr<ID3D11RenderTargetView>& GetRTView();
		const ID3D11RenderTargetView* GetRTViewRaw();

		void SetViewport(Viewport* vp);
		void AddDxViewPort(float top, float left, float width, float height, float minDepth, float maxDepth);
		void AddDxViewPort(D3D11_VIEWPORT dVp);
		Viewport* GetViewport();


	};

}

