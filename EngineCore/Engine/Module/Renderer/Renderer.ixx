#include "pch.h"
export module Renderer;
import Module;

export namespace F
{
	class Shader;
	class Mesh;
	class RenderContext;
	class Agent;
	class Renderer : public Module
	{
	private:
		Shader* shader;
		Mesh* mesh;

	public:
		Renderer();

		void Update(float dt) override;
		void Render(ID3D11DeviceContext* context) override;

		void SetMesh(Mesh* mesh) { this->mesh = mesh; }




	};

}