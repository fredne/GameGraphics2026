#pragma once

namespace F
{
	class RenderTarget;
	class RenderContext
	{
		static ID3D11DeviceContext* mainContext;
		RenderTarget* renderTarget;
		Color clearColor;

	public:
		RenderContext();
		~RenderContext();

		void Clear();
		void Bind();
		void SwapChain();

		static ID3D11DeviceContext* GetMainContext();
		static void SetMainContext(ID3D11DeviceContext* context);

		RenderTarget* CurrentRenderTarget();
		void SetRenderTarget(RenderTarget* rt);
		void SetClearColor(Color color);

	};

}
