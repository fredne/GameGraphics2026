#include "pch.h"
import Keyboard;
import InputSystem;

namespace F
{
	void InputSystem::Initialize()
	{
		Keyboard::Get().Initialize();
	}

	void InputSystem::Update()
	{
		Keyboard::Get().Update();
	}


}