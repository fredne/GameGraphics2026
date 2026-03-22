#pragma once

namespace F
{
	class Shader;
	class RenderContext;
	class Renderer
	{
	private:
		Shader* shader;

		void Render(RenderContext* ctx);
	};

}
