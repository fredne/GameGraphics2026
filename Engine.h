#pragma once

namespace F
{
	class RenderContext;
	class Engine
	{
	private:

	public:
		void Initialize();
		void Update();
		void Render(RenderContext* ctx);
	};

}
