#include "pch.h"
import Debug;
#include <chrono>
import Time;

namespace F
{
	Time::Time() :
		curTime(), prevTime(), delta(),
		deltaTime(0), totalTime(0), timeScale(1)
	{
	}
	void Time::Initialize()
	{
		prevTime = std::chrono::steady_clock::now();
	}

	void Time::Update()
	{
		curTime = std::chrono::steady_clock::now();
		delta = curTime - prevTime;
		deltaTime = delta.count();
		prevTime = curTime;

	}

	void Time::Render()
	{
	}

	void Time::Log()
	{
		F::Debug::Log(std::to_wstring(DeltaTime()).c_str());
	}

	float Time::DeltaTime() const { return deltaTime * timeScale; }
	float Time::TotalTime() const { return totalTime; }

}

