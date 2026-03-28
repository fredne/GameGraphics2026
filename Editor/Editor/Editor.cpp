#include "pch.h"
import Editor;
import EngineCore;
import Debug;

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

namespace F
{
	void Editor::Initialize()
	{
		EngineCore::Get().OnUpdate = [this]() 
		{
			Update();
		};
		EngineCore::Get().OnRender = [this]()
		{
			Render();
		};
	}

	void Editor::Release()
	{
	}

	void Editor::Update()
	{
		Debug::Log("GDGDGDGDG");
	}

	void Editor::Render()
	{
		//GUI
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("New Window");
		static std::string text = "Test text";
		ImGui::Text(text.c_str());
		if (ImGui::Button("Test Button"))
		{
			text = "AAAAAAAAAAAAAAAAAAAAAAAAAAa";
		}
		static float count = 0;
		ImGui::SliderFloat("Count", &count, 0, 100);
		ImGui::End();

		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

}