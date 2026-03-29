#include "pch.h"
import Monitor;

namespace F
{
	Monitor::Monitor()
	{
        IDXGIFactory* factory = nullptr;
        CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);

        IDXGIAdapter* adapter = nullptr;
        IDXGIOutput* output = nullptr;
        if (factory->EnumAdapters(0, &adapter) != DXGI_ERROR_NOT_FOUND and
            adapter->EnumOutputs(0, &output) != DXGI_ERROR_NOT_FOUND)
        {
            DXGI_OUTPUT_DESC outputDesc;
            output->GetDesc(&outputDesc);
            
            resolution.x = outputDesc.DesktopCoordinates.right - outputDesc.DesktopCoordinates.left;
            resolution.y = outputDesc.DesktopCoordinates.bottom - outputDesc.DesktopCoordinates.top;

            UINT modeCount = 0;
            output->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &modeCount, nullptr);
            std::vector<DXGI_MODE_DESC> displayModes(modeCount);
            output->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &modeCount, &displayModes[0]);
            
            for (const auto& mode : displayModes)
                refreshRateSet.insert((float)mode.RefreshRate.Numerator / mode.RefreshRate.Denominator);
        }

        output->Release();
        adapter->Release();
        factory->Release();
	}

    const Vector2& Monitor::GetResolution() { return resolution; }
}