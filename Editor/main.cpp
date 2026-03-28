#include "pch.h"
import Window;
import EngineCore;
import Debug;
import ResourceArchive;
import Editor;
using namespace F;

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
#ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(373);
#endif


    // Initialize Engine.
    EngineCore::Get().Initialize(hInstance);
    Editor::Get().Initialize();

    MSG msg = {};
    EngineCore::Get().Run(msg);

    Editor::Get().Release();
    EngineCore::Get().Release();

    return (int)msg.wParam;
}


