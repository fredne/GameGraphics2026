#pragma once

namespace F
{
	class RenderTarget;
	class RenderContext
	{
		ID3D11DeviceContext* mainContext = nullptr;

		RenderTarget* renderTarget;
		ID3D11RenderTargetView* dxRenderTargetView;
		Color clearColor;

	public:
		RenderContext(ID3D11DeviceContext* context);
		~RenderContext();

		void Draw(int count);
		void Clear();

		ID3D11DeviceContext* GetMainContext();

		RenderTarget* CurrentRenderTarget();
		void SetRenderTarget(RenderTarget* rt);
		void SetClearColor(Color color);

	};

}
