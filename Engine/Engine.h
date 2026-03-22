#pragma once

namespace F
{
	class DX;
	class Window;
	class Shader;
	class Model;
	class RenderContext;
	class Engine
	{
	private:
		std::vector<std::unique_ptr<F::Model>> modelList;
		Shader* defalutShader;
		DX* dx;
		bool a;
		bool isRunning ;

	public:
		Engine(Window* window);
		~Engine();

		void Initialize();
		void Run(MSG msg);
		bool ProcessInput(MSG msg);
		void Update();
		void Render();


		Shader* GetShader();

	};

}
