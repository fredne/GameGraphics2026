#include "pch.h"
#include <chrono>;
export module Time;

export namespace F
{
	class Time
	{
		std::chrono::steady_clock::time_point curTime;
		std::chrono::steady_clock::time_point prevTime;
		std::chrono::duration<float> delta;

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

		float DeltaTime() const;
		float TotalTime() const;
		float timeScale;

	};
}



