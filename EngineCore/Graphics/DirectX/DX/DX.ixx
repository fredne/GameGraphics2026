#include "pch.h"
export module DX;
export import RenderContext;
export import RenderTarget;
export import Shader;
export import ConstantBuffer;

export namespace F
{
	class RenderTarget;
	class Window;
	class DX
	{
		friend class EnigneCore;

		DX();

		void CreateDeviceAndSwapChain(Window* window);
		void CreateConstanctBuffer();

	public:
		ComPtr<ID3D11Device> device;
		ComPtr<ID3D11DeviceContext> mainContext;
		ComPtr<IDXGISwapChain> swapChain;
		RenderTarget* backBuffer;
		ConstantBuffer0* cBuffer0;

		static DX& Get()
		{
			static DX instance;
			return instance;
		}
		~DX();

		void Initialize(Window* window);
		void Release();

		void BeginRender();
		void SwapChain();

		void ResizeBackBuffer(uint32_t width, uint32_t height);

	};

}

