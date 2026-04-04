#include "pch.h"
export module PlayerController;
import Module;

export namespace F
{
	class PlayerController : public Module
	{
	private:
		float speed = 4;
		Vector3 velocity;
		float drag = 0.01f;

	public:

		void Initialize() override;
		void Update(float dt) override;
	
	};

}