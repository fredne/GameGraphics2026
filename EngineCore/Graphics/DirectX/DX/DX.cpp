#include "pch.h"
import DX;
import EngineCore;    
import Window;
import Debug;
import ConstantBuffer;
import RenderTarget;

ComPtr<ID3D11Buffer> cBuffer0;

namespace F
{
    DX::DX()
    {

    }
    DX::~DX()
    {

    }

    void DX::Initialize(Window* window)
    {
        CreateDeviceAndSwapChain(window);
        CreateConstanctBuffer();

        Vector2 windowSize = window->GetWindowSize();
        backBuffer = new RenderTarget({ 0, 0, windowSize.x, windowSize.y, 0.0, 0.1f });
        backBuffer->SetClearColor({ 0.1f, 0.2f, 0.3f, 0.4f });

    }

    void DX::Release()
    {
        if (cBuffer0) delete cBuffer0; cBuffer0 = nullptr;
        if (backBuffer) delete backBuffer; backBuffer = nullptr;
    }

    void DX::CreateDeviceAndSwapChain(Window* window)
    {
        HWND hWnd = window->GetWindowHandle();
        Vector2 windowSize = window->GetWindowSize();

        DXGI_SWAP_CHAIN_DESC scd = {};
        scd.BufferCount = 2;
        scd.BufferDesc.Width = windowSize.x;
        scd.BufferDesc.Height = windowSize.y;
        scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        scd.OutputWindow = hWnd;
        scd.SampleDesc.Count = 1;
        scd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        scd.Windowed = TRUE;
        //scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;

#ifdef DEBUG
        UINT flags = D3D11_CREATE_DEVICE_DEBUG;
#else
        UINT flags = 0;
#endif // DEBUG

        D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, flags, nullptr, 0,
            D3D11_SDK_VERSION, &scd, &swapChain, &device, nullptr, &mainContext);

    }

    void DX::CreateConstanctBuffer()
    {
        cBuffer0 = new ConstantBuffer0();
    }

    void DX::BeginRender()
    {
        backBuffer->BindAsTarget(mainContext.Get(), nullptr);
        backBuffer->ClearColor(mainContext.Get());
    }

    void DX::SwapChain()
    {
        //swapChain->Present(0, DXGI_PRESENT_ALLOW_TEARING);
        swapChain->Present(0, 0);
    }

}

