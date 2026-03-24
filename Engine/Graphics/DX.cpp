#include "pch.h"
#include "DX.h"
#include "RenderContext.h"
import RenderTarget;
#include "Shader/Shader.h"
import Window;
import Debug;
import Engine;    
import ConstantBuffer;

ComPtr<ID3D11Buffer> cBuffer0;

namespace F
{
    DX::DX()
    {

    }
    DX::~DX()
    {

    }

    void DX::Release()
    {
        if (cBuffer0) delete cBuffer0; cBuffer0 = nullptr;
        //if (cBuffer0) cBuffer0->Release();
        //if (swapChain) swapChain->Release(); swapChain = nullptr;
        //if (mainContext) mainContext->Release();  mainContext = nullptr;
        //if (device) device->Release(); device = nullptr;
    }


    void DX::CreateDeviceAndSwapChain()
    {
        Window* window = Engine::Get().GetWindow();
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

        UINT flags = D3D11_CREATE_DEVICE_DEBUG;
        D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, flags, nullptr, 0,
            D3D11_SDK_VERSION, &scd, &swapChain, &device, nullptr, &mainContext);

        CreateConstanctBuffer();
    }

    void DX::CreateRenderTargetView(RenderTarget* target)
    {
        ComPtr<ID3D11Texture2D> backBuffer = nullptr;
        swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
        DX::Get().device->CreateRenderTargetView(backBuffer.Get(), nullptr, &target->GetRTView());
    }

    void DX::CreateConstanctBuffer()
    {
        cBuffer0 = new ConstantBuffer0();

    }

    void DX::SwapChain()
    {
        //swapChain->Present(0, DXGI_PRESENT_ALLOW_TEARING);
        swapChain->Present(0, 0);
    }

}

