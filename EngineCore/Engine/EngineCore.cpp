#include "pch.h"
import EngineCore;
import Window;
import Monitor;
import DX;
import VertexBuffer;
import RenderTargetArchive;
import ResourceArchive;
import ShaderArchive;
import Transform;
import Debug;
import Keyboard;
import Model;
import Material;

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"


namespace F
{
    Transform* EngineCore::cameraTransform = nullptr;
    EngineCore::EngineCore() :
        alreadyInit(false), isRunning(true), 
        fpsCount(0), fps(0), elapsed(0)
    {
        cameraTransform = new Transform();
        cameraTransform->position.x = 1;
    }
    EngineCore::~EngineCore()
    {
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

        // ImGui
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);

        ImGui::StyleColorsDark();

        ImGui_ImplWin32_Init(hWnd);
        ImGui_ImplDX11_Init(dx.device.Get(), dx.mainContext.Get());


        float offsetY = 0.1f;
        std::vector<Vertex> vertices = {
            {  0.0f,  0.5f + offsetY, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f },
            {  0.5f, -0.5f + offsetY, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f },
            { -0.5f, -0.5f + offsetY, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f },

            {  0.0f, -0.5f - offsetY, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f },
            { -0.5f,  0.5f - offsetY, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f },
            {  0.5f,  0.5f - offsetY, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f },
        };
        std::unique_ptr<Model> model = std::make_unique<Model>();
        model->vBuffer = new VertexBuffer(vertices);
        modelList.push_back(move(model));

        // System
        Time::Get().Initialize();
        InputSystem::Get().Initialize();

        // Archive
        ResourceArchive::Get().Initialize();
        ShaderArchive::Get().Initialize();


    }
    void EngineCore::Release()
    {

        // System
        //Time::Get().Release();
        //InputSystem::Get().Release();

        // Archive
        ResourceArchive::Get().Release();
        ShaderArchive::Get().Release();

        for (auto& model : modelList)
        {
            model->Release();
        }

        if (cameraTransform)
        {
            delete cameraTransform;
            cameraTransform = nullptr;
        }

        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();

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



    void EngineCore::Run(MSG& msg)
    {
        while (isRunning)
        {
            ProcessInput(msg);
            Update();
            Render();
        }
    }

    void EngineCore::ProcessInput(MSG& msg)
    {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                isRunning = false;

            TranslateMessage(&msg);
            DispatchMessage(&msg);

        }
    }

    void EngineCore::Update()
    {
        // Service
        Time::Get().Update();
        InputSystem::Get().Update();

        //Time::Get().Log();

        if (Keyboard::Get().space.IsPressedNow())
        {
            float ts = Time::Get().timeScale;
            if (ts < 1)
                Time::Get().timeScale = 1;
            else
                Time::Get().timeScale = .1f;
        }

        float dt = Time::Get().DeltaTime();
        elapsed += dt;
        fpsCount++;
        //Debug::Log(std::to_string(fpsCount));
        if (elapsed >= 1)
        {
            elapsed -= 1;
            fps = fpsCount;
            fpsCount = 0;
            //Debug::Log("FPS: " + std::to_string(fps) + ", dt: " + std::to_string(dt));
        }

        // Model
        for (auto& model : modelList)
        {
            model->Update(dt);
        }

        if(OnUpdate) 
            OnUpdate();

    }

    void EngineCore::Render()
    {
        DX& dx = DX::Get();
        dx.BeginRender();

        Shader* shader = ShaderArchive::Get().Fetch<Shader>("DefaultShader");
        shader->Bind(renderContext->GetMainContext());
        for (auto& model : modelList)
        {
            model->Render(renderContext->GetMainContext());
        }


        if(OnRender)
            OnRender();



        dx.SwapChain();
    }

    void EngineCore::OnResize(UINT width, UINT height)
    {
        DX::Get().mainContext.Get()->OMSetRenderTargets(0, nullptr, nullptr);
    }


    DirectX::XMMATRIX EngineCore::GetCameraMatrix()
    {
        XMMATRIX R = XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&cameraTransform->rotation));
        XMVECTOR eye = XMLoadFloat3(&cameraTransform->position);
        XMVECTOR forward = XMVector3TransformNormal(XMVectorSet(0, 0, 1, 0), R);
        XMVECTOR target = eye + forward;

        return XMMatrixLookAtLH(eye, target, XMVectorSet(0, 1, 0, 0));
    }

    Window* EngineCore::GetWindow() { return window; }

}