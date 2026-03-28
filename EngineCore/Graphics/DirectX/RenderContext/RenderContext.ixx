#include "pch.h"
export module RenderContext;

export namespace F
{
	class Window;
	class RenderTarget;
	class RenderContext
	{
		static ID3D11DeviceContext* mainContext;
		RenderTarget* renderTarget;
		Color clearColor;

	public:
		RenderContext(Vector2 size);
		~RenderContext();

		static ID3D11DeviceContext* GetMainContext();
		static void SetMainContext(ID3D11DeviceContext* context);

		RenderTarget* CurrentRenderTarget();
		void SetRenderTarget(RenderTarget* rt);
		void SetClearColor(Color color);

	};

}
