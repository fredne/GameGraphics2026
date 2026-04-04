#include "pch.h"
import WorldArchive;
import TestWorld;
import Agent;

namespace F
{
	void WorldArchive::Initialize()
	{
		Register<TestWorld>("TestWorld");
	}


}