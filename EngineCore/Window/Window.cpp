#include "pch.h"
import Window;
import EngineCore;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);

namespace F
{
    Window::Window(HINSTANCE hInstance, int width, int height, std::wstring title = L"Window") :
        size(width, height), title(title)
    {
        if (!InitWindow(hInstance)) OutputDebugStringA("Failed Initialize Window");
    }

    bool Window::InitWindow(HINSTANCE hInstance)
	{
        const wchar_t* cTitle = title.c_str();

        size.x = 800;
		size.y = 600;
        RECT rect = { 0, 0, size.x, size.y };
        AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

        WNDCLASSEXW wcex = {};
        wcex.cbSize = sizeof(WNDCLASSEX);
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = WndProc;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = hInstance;
        //wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAMEGRAPHICS));
        wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wcex.lpszMenuName = NULL;
        wcex.lpszClassName = cTitle;
        //wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

        if (!RegisterClassExW(&wcex))
        {
            OutputDebugStringA("RegisterClass failed");
            return false;
        }

        hWnd = CreateWindowW(cTitle, cTitle, WS_OVERLAPPEDWINDOW,
            100, 100, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, hInstance, nullptr);

        if (!hWnd)
        {
            OutputDebugStringA("Window is null");
            return false;
        }

        ShowWindow(hWnd, SW_NORMAL);
        UpdateWindow(hWnd);

        return true;
	}

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_SIZE:
        if (wParam == SIZE_MAXIMIZED || wParam == SIZE_RESTORED)
        {
            UINT width = LOWORD(lParam);
            UINT height = HIWORD(lParam);
            F::EngineCore::Get().OnResize(width, height);
        }   
    default:
        break;
    }

    if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
        return true;

    return DefWindowProc(hWnd, message, wParam, lParam);
}