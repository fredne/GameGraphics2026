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
	class Mesh;
	class RenderContext;
	class RenderTarget;
	class Transform;
	class Monitor;
	class Agent;
	class World;
	class EngineCore
	{
	private:
		RenderContext* renderContext;
		Window* window;
		Monitor* monitor;
		bool isRunning;
		static Transform* cameraTransform;

		Mesh* triangle;

		std::unique_ptr<World> world;

		bool alreadyInit;
		float targetFPS;
		int fpsCount;
		int fps;
		float elapsed;

		EngineCore();
		void DebugDx();

	public:
		std::function<void()> OnInitialize;
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

		void OnResize(UINT width, UINT height);

		static DirectX::XMMATRIX GetCameraMatrix();

		Window* GetWindow();
		Shader* GetShader();

		void SetTargetFPS(int fps);

	};

}
