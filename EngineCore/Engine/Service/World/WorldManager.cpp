#include "pch.h"
import WorldManager;
import World;
import Agent;
import TestWorld;
import WorldArchive;

namespace F
{
	void WorldManager::Initialize()
	{

	}
	void WorldManager::Release()
	{
		if (currentWorld)
			currentWorld->Exit();
	}

	void WorldManager::Update(float dt)
	{
		currentWorld->Update(dt);
	}
	void WorldManager::Render(ID3D11DeviceContext* context)
	{
		currentWorld->Render(context);
	}

}