#include "pch.h"	
import TestWorld;
import MeshArchive;
import Agent;
import CameraAgent;
import Renderer;
import PlayerController;
import PC;
import TestModule;

namespace F
{
	void TestWorld::Enter()
	{
        std::unique_ptr<CameraAgent> cameraAg = std::make_unique<CameraAgent>();
        cameraAg->GetModule<Transform>()->position = { -0.5f, 0.1f, 0.f };
        AddAgent(std::move(cameraAg));

        std::unique_ptr<Agent> ag1 = std::make_unique<Agent>();
        Renderer* renderer = ag1->AddModule<Renderer>();
        renderer->SetMesh(MeshArchive::Get().Fetch<Mesh>("Triangle"));
        renderer->SetColor({ 1, 1, 1, 1 });
        ag1->AddModule<PlayerController>();
        ag1->AddModule<TestModule>();
        AddAgent(std::move(ag1));

        std::unique_ptr<Agent> ag2 = std::make_unique<Agent>();
        renderer = ag2->AddModule<Renderer>();
        renderer->SetMesh(MeshArchive::Get().Fetch<Mesh>("Triangle"));
        renderer->SetColor({ 0, 0, 0, 1 });
        ag2->AddModule<PC>();
        AddAgent(std::move(ag2));

	}

	void TestWorld::Exit()
	{
	}


}