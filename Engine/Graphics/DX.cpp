#include "pch.h"
#include "DX.h"
#include "Window/Window.h"
#include "RenderContext.h"
#include "RenderTarget.h"
#include "Shader/Shader.h"
#include "Debug/Debug.h"

ID3D11Buffer* cBuffer0;
ConstantBuffer0 cb0;

namespace F
{
    ID3D11Device* DX::device = nullptr;
    ID3D11DeviceContext* DX::context = nullptr;
    IDXGISwapChain* DX::swapChain = nullptr;

    DX::DX(Window* window)
    {
        InitD3D(window);

    }
    DX::~DX()
    {
        if (cBuffer0) cBuffer0->Release();

        if (swapChain) swapChain->Release();
        if (device) device->Release();
    }

    void DX::InitD3D(Window* window)
    {
        HWND hWnd = window->GetWindowHandle();
        Vector2 windowSize = window->GetWindowSize();

        DXGI_SWAP_CHAIN_DESC scd = {};
        scd.BufferCount = 1;
        scd.BufferDesc.Width = windowSize.x;
        scd.BufferDesc.Height = windowSize.y;
        scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        scd.OutputWindow = hWnd;
        scd.SampleDesc.Count = 1;
        scd.Windowed = TRUE;

        D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0,
            D3D11_SDK_VERSION, &scd, &swapChain, &device, nullptr, &context);

        // RenderTarget
        D3D11_VIEWPORT viewPort = { 0, 0, windowSize.x, windowSize.y, 0.0, 0.1f };
        defalutRT = new RenderTarget(swapChain, viewPort);
        renderContext = new RenderContext(context);
        renderContext->SetRenderTarget(defalutRT);


        
        // Constanct Buffer;
        D3D11_BUFFER_DESC desc = {};
        desc.ByteWidth = sizeof(ConstantBuffer0);
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        device->CreateBuffer(&desc, 0, &cBuffer0);

    }

    void DX::SwapChain()
    {
        swapChain->Present(0, 0);
    }

    RenderContext* DX::GetRenderContext() { return renderContext; }
}

