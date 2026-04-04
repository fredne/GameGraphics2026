#include "pch.h"
export module TestModule;
import Module;

export namespace F
{
	class TestModule : public Module
	{
	private:
		int fpsCount = 0, fps = 0;
		float elapsed = 0;

		void FPSUpdate(float dt);

	public:
		void Update(float dt) override;


	};

}