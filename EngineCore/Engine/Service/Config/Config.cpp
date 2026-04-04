#include "pch.h"
import Config;
import EngineCore;
import Keyboard;
import Window;

namespace F
{
    void Config::Update()
    {
        VideoModeUpdate();
    }

    void Config::VideoModeUpdate()
    {
        if (Keyboard::Get().fKey.IsPressedNow())
        {
            videoMode.fullscreen = !videoMode.fullscreen;
            EngineCore::Get().SetFullscreen(videoMode.fullscreen);
        }

        if (Keyboard::Get().key1.IsPressedNow())
        {
            videoMode.resolution = { 1280, 960 };
            videoMode.mustResize = true;
        }
        if (Keyboard::Get().key2.IsPressedNow())
        {
            videoMode.resolution = { 800, 600 };
			videoMode.mustResize = true;
        }
        if (videoMode.mustResize)
        {
            videoMode.Resize(EngineCore::Get().GetWindow());
            videoMode.mustResize = false;
		}
    }

	void VideoMode::Resize(Window* window)
	{
		if (not fullscreen)
		{
			RECT rect = { 0, 0, resolution.x, resolution.y };
			AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
			SetWindowPos(window->GetWindowHandle(), NULL, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE | SWP_NOZORDER);
            EngineCore::Get().OnResize(resolution);
        }

	}
}