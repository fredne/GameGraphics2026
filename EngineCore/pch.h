#pragma once
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
#include <windows.h>
#include <SDKDDKVer.h>

// DirectX
#include <d3d11.h>
#include <d3dcompiler.h>

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iostream>
#include <dxgidebug.h>
#pragma comment(lib, "dxguid.lib")
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#endif

#include <DirectXMath.h>
using namespace DirectX;

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <wrl/client.h>
using Microsoft::WRL::ComPtr;

#include <string>
#include <format>
#include <memory>
#include <set>
#include <vector>
#include <unordered_map>
#include <thread>

#include "Common.h"