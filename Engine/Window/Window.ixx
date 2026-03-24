#include "pch.h"
export module Window;

export namespace F
{
    class Window
    {
        HINSTANCE hInst;
        HWND hWnd;
        std::wstring title;
        Vector2 size;

    public:
        Window(HINSTANCE hInstance, int width, int height, std::wstring title);
        bool InitWindow(HINSTANCE hInstance);
        HWND GetWindowHandle() const;

        Vector2 GetWindowSize();


    };

}
