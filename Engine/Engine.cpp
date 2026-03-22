#include "pch.h"
#include "Engine.h"
#include "../Model.h"
#include "VertexBuffer.h"
#include "Time/Time.h"
#include "RenderContext.h"
#include "DX.h"
#include "Shader/Shader.h"
#include "Material/Material.h"
#include "Debug/Debug.h"
#include "ResourceArchive.h"

namespace F
{
    Engine::Engine(Window* window) :
        defalutShader(nullptr),
        a(false), isRunning(true)
    {
        dx = new DX(window);
        dx->GetRenderContext()->SetClearColor({ 0.1f, 0.2f, 0.3f, 0.4f });

        ResourceArchive::Get().Register<Resource>("AA");
        auto a = ResourceArchive::Get().Fetch<Resource>("AA");
        if (a)
        {
            Debug::Log("AA is alive");
        }

    }
    Engine::~Engine()
    {
        if (defalutShader) delete defalutShader;
        if (dx) delete dx;
    }

    void Engine::Initialize()
	{
        // Shader
        defalutShader = new Shader(L"VertexShader.cso", L"PixelShader.cso");
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


        Time::Get().Initialize();

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

    bool Engine::ProcessInput(MSG msg)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                isRunning = false;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
            return true;

        }
        return false;
    }

	void Engine::Update()
	{
        // Time
        Time::Get().Update();

        if ((GetAsyncKeyState(VK_SPACE) && 0x0008) && !a)
        {
            Time::Get().timeScale = .1f;
            a = true;
        }

        // Model
        for (auto& model : modelList)
        {
            model->Update(Time::Get().DeltaTime());
        }
	}

	void Engine::Render()
	{
        RenderContext* ctx = dx->GetRenderContext();
        ctx->Clear();
        ctx->Draw(0);

        //Time::Get().Render();
        
        defalutShader->Bind(ctx->GetMainContext());
        for (auto& model : modelList)
        {
            model->Render(ctx->GetMainContext());
        }

        DX::SwapChain();
	}


    Shader* Engine::GetShader() { return defalutShader; }

}