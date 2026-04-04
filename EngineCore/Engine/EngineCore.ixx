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
		MSG msg = {};
		Monitor* monitor;
		bool isRunning;
		//static Transform* cameraTransform;

		bool alreadyInit;
		bool alreadyRelease;

		float targetFPS;
		bool enableFrameLimit;

		EngineCore();
		void DebugDx();

	public:
		std::function<void()> OnInitialize;
		std::function<void()> OnRelease;
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
		void Run();
		void ProcessInput();
		void Update();
		void Render();

		void OnResize(uint32_t width, uint32_t height);
		void OnResize(const Vector2<uint32_t>& resolution);

		Window* GetWindow() { return window; }
		MSG& GetMsg() { return msg; }

		void EnableFrameLimit(bool enable);
		void SetTargetFPS(int fps);
		void LimitFPS();

		void SetFullscreen(bool fullscreen);

	};

}
