#pragma once

namespace F
{
	class Time
	{
		LARGE_INTEGER freq;
		LARGE_INTEGER curCT;
		LARGE_INTEGER prevCT;

		float deltaTime;
		float totalTime;

	public:
		static Time& Get()
		{
			static Time instance;
			return instance;
		}

		Time();

		void Initialize();
		void Update();
		void Render();

		float DeltaTime();
		float TotalTime();
		float timeScale;

	};
}



