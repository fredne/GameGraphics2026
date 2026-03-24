#include "pch.h"
import Window;
import Engine;
#include "ResourceArchive.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
using namespace DirectX;
using namespace std;

// 전역 변수:
HINSTANCE hInst;                                
HWND hWnd;
UINT width = 600;
UINT height = 600;


int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine,_In_ int nCmdShow)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(373);

    MSG msg = {};

    // Initialize Window
    F::Window window(hInstance, width, height, L"ZZZZ");
    hWnd = window.GetWindowHandle();
    if (!hWnd) return 0;

    // Initialize Engine.
    F::Engine& engine = F::Engine::Get();
    engine.Initialize(&window);
    engine.Run(msg);
    engine.Release();
  
    return (int) msg.wParam;
}

