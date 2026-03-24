#include "pch.h"
import Window;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

namespace F
{
    Window::Window(HINSTANCE hInstance, int width, int height, std::wstring title = L"Window") :
        size(width, height), title(title)
    {
        if (!InitWindow(hInstance)) OutputDebugStringA("Failed Initialize Window");
    }

    bool Window::InitWindow(HINSTANCE hInstance)
	{
        PCWCHAR cTitle = title.c_str();

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
            500, 300, size.x, size.y, nullptr, nullptr, hInstance, nullptr);

        if (!hWnd)
        {
            OutputDebugStringA("Window is null");
            return false;
        }

        ShowWindow(hWnd, SW_SHOW);
        UpdateWindow(hWnd);

        return true;
	}

    HWND Window::GetWindowHandle() const { return hWnd; }

    Vector2 Window::GetWindowSize() { return size; }


}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_KEYDOWN:
        break;
    case WM_KEYUP:
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}