#include "pch.h"
export module Module;

export namespace F
{
	class Agent;
	class Module
	{
	private:
		Agent* agent;

	public:
		virtual ~Module();
		virtual void Update() = 0;

	};

}
;