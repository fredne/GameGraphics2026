#include "pch.h"
#include "Time.h"
#include "Debug/Debug.h"

namespace F
{
	Time::Time() :
		deltaTime(0), totalTime(0), timeScale(1)
	{
	}
	void Time::Initialize()
	{
		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&prevCT);
	}

	void Time::Update()
	{
		QueryPerformanceCounter(&curCT);
		deltaTime = (float)(curCT.QuadPart - prevCT.QuadPart) / freq.QuadPart;
		totalTime += deltaTime * timeScale;
		prevCT = curCT;
	}

	void Time::Render()
	{
		F::Debug::Log(std::to_wstring(DeltaTime()).c_str());
	}

	float Time::DeltaTime() { return deltaTime * timeScale; }
	float Time::TotalTime() { return totalTime; }

}

