#pragma once
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
#include <windows.h>
#include <SDKDDKVer.h>

// DirectX
#include <d3d11.h>
#include <d3dcompiler.h>
#ifdef _DEBUG
#include <dxgidebug.h>
#pragma comment(lib, "dxguid.lib")
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
#include <vector>
#include <set>
#include <memory>
#include <unordered_map>

#include "Common.h"