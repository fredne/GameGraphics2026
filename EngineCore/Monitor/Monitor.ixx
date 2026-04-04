#include "pch.h"
export module Monitor;

export namespace F
{
	class Monitor
	{
	private:
		std::set<float> refreshRateSet;
		Vector2<float> resolution;

	public:
		Monitor();
		~Monitor();

		const Vector2<float>& GetResolution() { return resolution; }


	};

}