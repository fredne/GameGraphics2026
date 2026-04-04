#include "pch.h"
export module TestWorld;
import World;

export namespace F
{
	class TestWorld : public World
	{
	public:
		virtual ~TestWorld() = default;
		void Enter() override;	
		void Exit() override;

	};

}