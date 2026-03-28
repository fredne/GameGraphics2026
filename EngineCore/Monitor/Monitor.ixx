#include "pch.h"
export module Monitor;

export namespace F
{
	class Monitor
	{
	private:
		std::set<float> refreshRateSet;
		Vector2 resolution;

	public:
		Monitor();

		const Vector2& GetResolution();


	};

}