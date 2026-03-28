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

        bool InitWindow(HINSTANCE hInstance);

    public:
        Window(HINSTANCE hInstance, int width, int height, std::wstring title);
        HWND GetWindowHandle() const;
        Vector2 GetWindowSize();


    };

}
