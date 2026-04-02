#include "pch.h"
import World;
import Agent;
import Module;

namespace F
{
	void World::Initialize()
	{
		for (auto& agent : agentList)
		{
			agent->Initialize();
		}
	}

	void World::Release()
	{
		for (auto& agent : agentList)
		{
			agent->Release();
		}
	}

	void World::Update(float dt)
	{
		for (auto& agent : agentList)
		{
			agent->Update(dt);
		}
	}
	void World::Render(ID3D11DeviceContext* context)
	{
		for (auto& agent : agentList)
		{
			agent->Render(context);
		}
	}

	Agent* World::AddAgent(std::unique_ptr<Agent> agent)
	{
		Agent* raw = agent.get();
		agentList.push_back(std::move(agent));
		return raw;
	}
}
