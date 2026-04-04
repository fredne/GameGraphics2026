#include "pch.h"
import Agent;
import Module;
import Transform;

namespace F
{
	Agent::Agent() :
		moduleList()
	{
		AddModule<Transform>();
	}

	void Agent::Initialize()
	{
		
	}
	void Agent::Update(float dt)
	{
		for (auto& mod : moduleList)
		{
			mod->Update(dt);
		}
	}

	void Agent::Render(ID3D11DeviceContext* context)
	{
		for (auto& mod : moduleList)
		{
			mod->Render(context);
		}
	}

	void Agent::Release()
	{

	}

}