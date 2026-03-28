#include "pch.h"
export module ImGuiManager;

export namespace F
{
	class ImGuiManager
	{
	public:
		void Initialize(HWND hWnd, ID3D11Device* device, ID3D11DeviceContext* context);
		void Begin();
		void End();
		void Shutdown();
	};
}