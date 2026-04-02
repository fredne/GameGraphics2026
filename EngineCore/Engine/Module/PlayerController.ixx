#include "pch.h"
export module PlayerController;
import Module;

export namespace F
{
	class PlayerController : public Module
	{
	private:
		float speed = 1;

	public:
		void Update(float dt) override;
	};

}