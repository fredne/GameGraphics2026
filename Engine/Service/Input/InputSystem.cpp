#include "pch.h"
#include "Keyboard/Keyboard.h"
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