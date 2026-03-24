#include "pch.h"
#include "../Model.h"
import VertexBuffer;
#include "RenderContext.h"
#include "DX.h"
#include "Shader/Shader.h"
#include "Material/Material.h"
#include "ResourceArchive.h"
#include "Keyboard/Keyboard.h"
import Engine;
import Transform;
import RenderTargetArchive;

namespace F
{
    Transform* Engine::cameraTransform = nullptr;
    Engine::Engine() :
        isRunning(true), fpsCount(0), fps(0), elapsed(0)
    {

        cameraTransform = new Transform();
        cameraTransform->position.x = 1;

    }
    Engine::~Engine()
    {

    }

    void Engine::Initialize(Window* window)
	{
        this->window = window;

        DX& dx = DX::Get();
        dx.CreateDeviceAndSwapChain();
        RenderContext::SetMainContext(dx.mainContext.Get());
        renderContext = new RenderContext();
        renderContext->SetClearColor({ 0.1f, 0.2f, 0.3f, 0.4f });

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

	}
    void Engine::Release()
    {

        // System
        //Time::Get().Release();
        //InputSystem::Get().Release();

        // Archive
        ResourceArchive::Get().Release();

        for (auto& model : modelList)
        {
            model->Release();
        }

        if (cameraTransform)
        {
            delete cameraTransform;
            cameraTransform = nullptr;
        }

        if (renderContext) delete renderContext;

        DX::Get().Release();
        //DebugDx();
    }
    void Engine::DebugDx()
    {
        //  ComPtr 해제 전 강제 표시
        HMODULE dxgidebugdll = GetModuleHandleW(L"dxgidebug.dll");
        decltype(&DXGIGetDebugInterface) GetDebugInterface = reinterpret_cast<decltype(&DXGIGetDebugInterface)>(GetProcAddress(dxgidebugdll, "DXGIGetDebugInterface"));
        IDXGIDebug* debug;
        GetDebugInterface(IID_PPV_ARGS(&debug));
        OutputDebugStringW(L"Starting Live Direct3D Object Dump:\r\n");
        debug->ReportLiveObjects(DXGI_DEBUG_D3D11, DXGI_DEBUG_RLO_DETAIL);
        OutputDebugStringW(L"Completed Live Direct3D Object Dump.\r\n");
        debug->Release();
    }

    void Engine::Run(MSG msg)
    {
        while (isRunning)
        {
            ProcessInput(msg);
            Update();
            Render();
        }
    }

    void Engine::ProcessInput(MSG msg)
    {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                isRunning = false;

            TranslateMessage(&msg);
            DispatchMessage(&msg);

        }
    }

	void Engine::Update()
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
            Debug::Log("FPS: " + std::to_string(fps) + ", dt: " + std::to_string(dt));
        }

        // Model
        for (auto& model : modelList)
        {
            model->Update(dt);
        }


	}

	void Engine::Render()
	{
        renderContext->Clear();
        renderContext->Bind();
        
        Shader* shader = ResourceArchive::Get().Fetch<Shader>("DefaultShader");
        shader->Bind(renderContext->GetMainContext());
        for (auto& model : modelList)
        {
            model->Render(renderContext->GetMainContext());
        }

        renderContext->SwapChain();
	}

    DirectX::XMMATRIX Engine::GetCameraMatrix()
    {
        XMMATRIX R = XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&cameraTransform->rotation));
        XMVECTOR eye = XMLoadFloat3(&cameraTransform->position);
        XMVECTOR forward = XMVector3TransformNormal(XMVectorSet(0, 0, 1, 0), R);
        XMVECTOR target = eye + forward;

        return XMMatrixLookAtLH(eye, target, XMVectorSet(0, 1, 0, 0));
    }

    Window* Engine::GetWindow() { return window; }

}