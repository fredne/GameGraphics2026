#include "pch.h"
import EngineCore;
import Window;
import Monitor;
import DX;
import RenderTargetArchive;
import ResourceArchive;
import ShaderArchive;
import MeshArchive;
import Keyboard;
import Mesh;
import Agent;
import World;
import TestWorld;
import Config;
import WorldArchive;
import WorldManager;

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

namespace F
{
    //Transform* EngineCore::cameraTransform = nullptr;
    EngineCore::EngineCore() :
        renderContext(nullptr), window(nullptr), monitor(nullptr),
        alreadyInit(false), alreadyRelease(false),
        isRunning(true),  enableFrameLimit(false)
    {
        EnableFrameLimit(false);
        SetTargetFPS(45);
    }
    EngineCore::~EngineCore()
    {
        Release();
    }

    void EngineCore::Initialize(HINSTANCE hInstance)
    {
        if (alreadyInit) return;
        alreadyInit = true;

        monitor = new Monitor();

        // Initialize Window
        Vector2 resolution = monitor->GetResolution();
        window = new Window(hInstance, resolution.x, resolution.y, L"FEngine Editor");
        HWND hWnd = window->GetWindowHandle();
        if (!hWnd) return;

        DX& dx = DX::Get();
        dx.Initialize(window);
        RenderContext::SetMainContext(dx.mainContext.Get());
        renderContext = new RenderContext(window->GetWindowSize());

        // System
        Time::Get().Initialize();
        InputSystem::Get().Initialize();
		WorldManager::Get().Initialize();

        // Archive
        ResourceArchive::Get().Initialize();
        ShaderArchive::Get().Initialize();
        MeshArchive::Get().Initialize();
        WorldArchive::Get().Initialize();

		WorldManager::Get().LoadWorld<TestWorld>("TestWorld");

        // Editor
        if (OnInitialize)
            OnInitialize();

    }
    void EngineCore::Release()
    {
        if (alreadyRelease) return;
		alreadyRelease = true;

        // System
        //Time::Get().Release();
        //InputSystem::Get().Release();
		WorldManager::Get().Release();

        // Archive
        ResourceArchive::Get().Release();
        ShaderArchive::Get().Release();
		MeshArchive::Get().Release();
		WorldArchive::Get().Release();

		// Editor
        if(OnRelease)
		    OnRelease();

        if (renderContext) delete renderContext;

        DX::Get().Release();
        //DebugDx();

        if (window) delete window;
        if (monitor) delete monitor;

    }
    void EngineCore::DebugDx()
    {
#ifdef _DEBUG
        //  ComPtr 해제 전 강제 표시
        HMODULE dxgidebugdll = GetModuleHandleW(L"dxgidebug.dll");
        decltype(&DXGIGetDebugInterface) GetDebugInterface = reinterpret_cast<decltype(&DXGIGetDebugInterface)>(GetProcAddress(dxgidebugdll, "DXGIGetDebugInterface"));
        IDXGIDebug* debug;
        GetDebugInterface(IID_PPV_ARGS(&debug));
        OutputDebugStringW(L"Starting Live Direct3D Object Dump:\r\n");
        debug->ReportLiveObjects(DXGI_DEBUG_D3D11, DXGI_DEBUG_RLO_DETAIL);
        OutputDebugStringW(L"Completed Live Direct3D Object Dump.\r\n");
        debug->Release();
#endif
    }


    void EngineCore::Run()
    {
        while (isRunning)
        {
            ProcessInput();
            Update();
            Render();

			LimitFPS();

        }
    }

    void EngineCore::ProcessInput()
    {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT || Keyboard::Get().esc.IsPressedNow())
                isRunning = false;

            TranslateMessage(&msg);
            DispatchMessage(&msg);

        }
    }

    void EngineCore::Update()
    {
        // Service
        InputSystem::Get().Update();
        Config::Get().Update();

        Time::Get().Update();
        float dt = Time::Get().DeltaTime();

		WorldManager::Get().Update(dt);

		// Editor
        if(OnUpdate) 
            OnUpdate();

    }

    void EngineCore::Render()
    {
        DX& dx = DX::Get();
        dx.BeginRender();
        
        WorldManager::Get().Render(dx.mainContext.Get());

        //if(OnRender)
        //    OnRender();

        dx.SwapChain();

    }

    void EngineCore::SetTargetFPS(int fps) { targetFPS = 1.f / (fps * 0.5f); }
    void EngineCore::EnableFrameLimit(bool enable) { enableFrameLimit = enable; }
    void EngineCore::LimitFPS()
    {
        if (not enableFrameLimit) return;

        float dt = Time::Get().DeltaTime();
        if (targetFPS - dt > 0)
        {
            std::this_thread::sleep_for(
                std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::duration<float>(targetFPS - dt)));
        }
    }

    void EngineCore::OnResize(uint32_t width, uint32_t height)
    {
        DX::Get().ResizeBackBuffer(width, height);
    }
    void EngineCore::OnResize(const Vector2<uint32_t>& resolution)
    {
        DX::Get().ResizeBackBuffer(resolution.x, resolution.y);
    }
    void EngineCore::SetFullscreen(bool fullscreen)
    {
        DX::Get().swapChain->SetFullscreenState(fullscreen, nullptr);
    }


}