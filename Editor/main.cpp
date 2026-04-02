#include "pch.h"
import Window;
import EngineCore;
import Debug;
import ResourceArchive;
import Editor;
using namespace F;
#include <timeapi.h>
#pragma comment(lib, "winmm.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
#ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(460);
#endif

    timeBeginPeriod(1);

    // Initialize Engine.
    EngineCore::Get().Initialize(hInstance);
    Editor::Get().Initialize();

    MSG msg = {};
    EngineCore::Get().Run(msg);

    Editor::Get().Release();
    EngineCore::Get().Release();

    timeEndPeriod(1);


    return (int)msg.wParam;
}


