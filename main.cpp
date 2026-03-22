#include "pch.h"
#include "Window/Window.h"
#include "Engine.h"
#include "ResourceArchive.h"
using namespace DirectX;
using namespace std;

// 전역 변수:
HINSTANCE hInst;                                
HWND hWnd;
UINT width = 600;
UINT height = 600;


int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine,_In_ int nCmdShow)
{
    MSG msg = {};

    // Initialize Window
    F::Window window(hInstance, width, height, L"ZZZZ");
    hWnd = window.GetWindowHandle();
    if (!hWnd) return 0;

    // Initialize Engine.
    F::Engine engine(&window);
    engine.Initialize();
    engine.Run(msg);

    return (int) msg.wParam;
}

