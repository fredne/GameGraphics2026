#include "pch.h"
export module PC;
import Module;

export namespace F
{
	class PC : public Module
	{
	private:
		float speed = 6;
		Vector3 velocity = 0;
		float drag = 0.01f;

	public:

		void Initialize() override;
		void Update(float dt) override;
	};

}