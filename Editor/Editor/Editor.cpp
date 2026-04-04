#include "pch.h"
import Editor;
import EngineCore;
import Debug;
import DX;
import Window;

#include "imgui.h"
#include "imgui_demo.cpp"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

namespace F
{
	Editor::Editor()
	{
		EngineCore::Get().OnInitialize = [this]() { Initialize(); };
		EngineCore::Get().OnRelease = [this]() { Release(); };
		EngineCore::Get().OnUpdate = [this]() { Update(); };
		EngineCore::Get().OnRender = [this]() { Render(); };

	}

	void Editor::Initialize()
	{
		ImGuiInit();
	}
	void Editor::ImGuiInit()
	{
		if (imguiInit) return;

		imguiInit = true;

		DX& dx = DX::Get();
		HWND hWnd = EngineCore::Get().GetWindow()->GetWindowHandle();

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);

		ImGui::StyleColorsDark();

		ImGui_ImplWin32_Init(hWnd);
		ImGui_ImplDX11_Init(dx.device.Get(), dx.mainContext.Get());

	}

	void Editor::Release()
	{
		if (not imguiInit or imguiRelease) return;
		imguiRelease = true;

		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}

	void Editor::Update()
	{
		//Debug::Log("Editor Update");
	}

	void Editor::Render()
	{
		//GUI
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		static bool opt_fullscreen = true;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// 1. 전체 화면 설정을 위한 윈도우 플래그
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen) {
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// 2. 배경 역할을 할 투명한 창 시작
		ImGui::Begin("MyEngineDockSpace", nullptr, window_flags);
		if (opt_fullscreen) ImGui::PopStyleVar(2);

		// 3. 실제 DockSpace ID 생성 및 실행
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}
		
		// 4. 테스트용 창
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

		ImGui::ShowDemoWindow();

		ImGui::End();

		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
	}

}