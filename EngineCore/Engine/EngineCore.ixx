#include "pch.h"
export module EngineCore;
export import Time;
export import InputSystem;
#include <functional>

export namespace F
{
	class DX;
	class Window;
	class Shader;
	class Model;
	class RenderContext;
	class Transform;
	class Monitor;
	class EngineCore
	{
	private:
		RenderContext* renderContext;
		Window* window;
		Monitor* monitor;
		bool isRunning;
		static Transform* cameraTransform;

		std::vector<std::unique_ptr<Model>> modelList;

		int fpsCount;
		int fps;
		float elapsed;
		bool alreadyInit;

		EngineCore();
		void DebugDx();
		void OnResize(UINT width, UINT height);

	public:
		std::function<void()> OnUpdate;
		std::function<void()> OnRender;

		static EngineCore& Get()
		{
			static EngineCore instance;
			return instance;
		}
		~EngineCore();

		void Initialize(HINSTANCE hInstance);
		void Release();
		void Run(MSG& msg);
		void ProcessInput(MSG& msg);
		void Update();
		void Render();
		


		static DirectX::XMMATRIX GetCameraMatrix();

		Window* GetWindow();
		Shader* GetShader();

	};

}
