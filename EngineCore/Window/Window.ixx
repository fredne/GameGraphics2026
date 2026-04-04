#include "pch.h"
export module Window;

export namespace F
{
    class Window
    {
        HINSTANCE hInst;
        HWND hWnd;
        std::wstring title;
        Vector2<float> size;

        bool InitWindow(HINSTANCE hInstance);

    public:
        Window(HINSTANCE hInstance, int width, int height, std::wstring title);
        HWND GetWindowHandle() const { return hWnd; }
        Vector2<float> GetWindowSize() const { return size; }

    };

}
