#include "pch.h"

export module Engine;
export import Time;
export import InputSystem;
export import Debug;

export namespace F
{
	class DX;
	class Window;
	class Shader;
	class Model;
	class RenderContext;
	class Transform;
	class Engine
	{
	private:
		RenderContext* renderContext;
		Window* window;
		bool isRunning;
		static Transform* cameraTransform;

		std::vector<std::unique_ptr<Model>> modelList;

		int fpsCount;
		int fps;
		float elapsed;

		void DebugDx();

		Engine();

	public:
		static Engine& Get()
		{
			static Engine instance;
			return instance;
		}
		~Engine();

		void Initialize(Window* window);
		void Release();
		void Run(MSG msg);
		void ProcessInput(MSG msg);
		void Update();
		void Render();

		static DirectX::XMMATRIX GetCameraMatrix();

		Window* GetWindow();
		Shader* GetShader();

	};

}
