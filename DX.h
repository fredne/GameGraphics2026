#pragma once

extern ID3D11Buffer* cBuffer0;
struct ConstantBuffer0
{
	DirectX::XMFLOAT4X4 world;
};
extern ConstantBuffer0 cb0;

struct IDXGISwapChain;

namespace F
{
	class RenderContext;
	class RenderTarget;
	class Window;
	class Shader;
	class DX
	{
		IDXGISwapChain* swapChain;
		RenderContext* renderContext;
		RenderTarget* defalutRT;
		Shader* defalutShader;

		void InitD3D(Window* window);

	public:
		static ID3D11Device* device;
		static ID3D11DeviceContext* context;

		DX(Window* window);
		~DX();

		void Render();
		void SwapChain();

		RenderContext* GetRenderContext();
		Shader* GetShader();


	};

}

