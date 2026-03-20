#include "pch.h"
#include "Window.h"
#include "DX.h"
#include "RenderContext.h"
#include "Shader.h"
#include "Debug.h"
#include "Transform.h"
#include "VertexBuffer.h"
#include "Model.h"
#include "Time.h"

using namespace DirectX;
using namespace std;

// 전역 변수:
HINSTANCE hInst;                                
HWND hWnd;
UINT width = 600;
UINT height = 600;
bool isRunning = true;

F::DX* dx;

vector<unique_ptr<F::Model>> modelList;

bool ProcessInput(MSG msg)
{
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        if(msg.message == WM_QUIT)
            isRunning = false;

        TranslateMessage(&msg);
        DispatchMessage(&msg);
        return true;

    }
    return false;
}
bool a = false;

void Update()
{
    // Time
    F::Time::Get().Update();
    
    if ((GetAsyncKeyState(VK_SPACE) && 0x0008) && !a)
    {
        F::Time::Get().timeScale = .1f;
        a = true;
    }

    // Model
    for (auto& model : modelList)
    {
        model->Update(F::Time::Get().DeltaTime());
    }

}

void Render(Color clearColor)
{
    F::Time::Get().Render();

    dx->GetRenderContext()->Clear();
    dx->GetRenderContext()->Draw(0);
    dx->GetShader()->Bind(dx->context);

    for (auto& model : modelList)
    {
        model->Render(dx->context);
    }

    dx->SwapChain();
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine,_In_ int nCmdShow)
{
    // Initialize Window
    F::Window window(hInstance, width, height, L"ZZZZ");
    hWnd = window.GetWindowHandle();
    if (!hWnd) return 0;

    // Initialize DirectX
    dx = new F::DX(&window);

    // Initialize etc.
    F::Time::Get().Initialize();

    // Vertex
    float offsetY = 0.1f;
    std::vector<Vertex> vertices = {
        {  0.0f,  0.5f + offsetY, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f },
        {  0.5f, -0.5f + offsetY, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f },
        { -0.5f, -0.5f + offsetY, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f },

        {  0.0f, -0.5f - offsetY, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f },
        { -0.5f,  0.5f - offsetY, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f },
        {  0.5f,  0.5f - offsetY, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f },
    };
    unique_ptr<F::Model> model = make_unique<F::Model>();
    model->vBuffer = new F::VertexBuffer(vertices);
    modelList.push_back(move(model));

    Color clearColor = { 0.1f, 0.2f, 0.3f, 0.4f };
    dx->GetRenderContext()->SetClearColor(clearColor);

    MSG msg = {};
    while (isRunning)
    {
        ProcessInput(msg);
        Update();
        Render(clearColor);
    }

    //for (auto& model : modelList)
    //{
    //    if (model) delete model;
    //}

    delete dx;

    return (int) msg.wParam;
}

