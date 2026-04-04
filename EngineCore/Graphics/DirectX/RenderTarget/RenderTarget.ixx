#include "pch.h"
export module RenderTarget;

export namespace F
{
	class Viewport;
	class RenderContext;
	class RenderTarget
	{
		ComPtr<ID3D11RenderTargetView> dxRTV;
		ComPtr<ID3D11ShaderResourceView> dxSRV;
		Viewport* viewport;
		Color clearColor;

		void Create();

	public:
		RenderTarget(D3D11_VIEWPORT dVp);
		~RenderTarget();

		void Reset();

		void ResizeRenderTarget(D3D11_VIEWPORT dxVp);

		void BindAsTarget(ID3D11DeviceContext* context, ID3D11DepthStencilView* dsv);
		void BindAsResource(ID3D11DeviceContext* context, uint32_t slot);
		void ClearColor(ID3D11DeviceContext* context);

		ID3D11RenderTargetView* GetRTV();
		ID3D11ShaderResourceView* GetSRV();

		void SetViewport(Viewport* vp);
		void AddDxViewPort(float top, float left, float width, float height, float minDepth, float maxDepth);
		void AddDxViewPort(D3D11_VIEWPORT dVp);
		Viewport* GetViewport();
		void SetClearColor(Color color);

		Vector2<uint32_t> GetCurrentRenderSize();

	};

}

