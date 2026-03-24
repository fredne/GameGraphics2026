#pragma once

namespace F
{
	
	class ConstantBuffer0;
	class RenderContext;
	class RenderTarget;
	class Window;
	class Shader;
	class DX
	{
		friend class Enigne;

		DX();

	public:
		ComPtr<ID3D11Device> device;
		ComPtr<ID3D11DeviceContext> mainContext;
		ComPtr<IDXGISwapChain> swapChain;
		ConstantBuffer0* cBuffer0;

		static DX& Get()
		{
			static DX instance;
			return instance;
		}
		~DX();

		void Release();

		void CreateDeviceAndSwapChain();
		void CreateRenderTargetView(RenderTarget* target);
		void CreateConstanctBuffer();
		void Render();
		void SwapChain();

	};

}

