#include "pch.h"
#include "Window.h"

bool moveInput[(int)Key::Last] = { false, };
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
        if (wParam == VK_ESCAPE) PostQuitMessage(0);
        if (wParam == VK_LEFT || wParam == 'A') moveInput[(int)Key::Left] = true;
        if (wParam == VK_RIGHT || wParam == 'D') moveInput[(int)Key::Right] = true;
        if (wParam == VK_UP || wParam == 'W') moveInput[(int)Key::Up] = true;
        if (wParam == VK_DOWN || wParam == 'S') moveInput[(int)Key::Down] = true;
        break;
    case WM_KEYUP:
        if (wParam == VK_ESCAPE) PostQuitMessage(0);
        if (wParam == VK_LEFT || wParam == 'A') moveInput[(int)Key::Left] = false;
        if (wParam == VK_RIGHT || wParam == 'D') moveInput[(int)Key::Right] = false;
        if (wParam == VK_UP || wParam == 'W') moveInput[(int)Key::Up] = false;
        if (wParam == VK_DOWN || wParam == 'S') moveInput[(int)Key::Down] = false;
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}