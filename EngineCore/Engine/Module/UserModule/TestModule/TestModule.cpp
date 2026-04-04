#include "pch.h"
import TestModule;
import Time;
import Keyboard;
import EngineCore;

namespace F
{
	void TestModule::Update(float dt)
	{
        FPSUpdate(dt);
	}

    void TestModule::FPSUpdate(float dt)
    {
        elapsed += dt;
        fpsCount++;
        if (elapsed >= 1)
        {
            elapsed -= 1;
            fps = fpsCount;
            fpsCount = 0;
            auto msg = std::format("FPS: {}, dt: {}", fps, dt);
            std::cout << msg << std::endl;
        }

        if (Keyboard::Get().space.IsPressedNow())
        {
            float ts = Time::Get().timeScale;
            if (ts < 1)
                Time::Get().timeScale = 1;
            else
                Time::Get().timeScale = .1f;
        }
    }

}