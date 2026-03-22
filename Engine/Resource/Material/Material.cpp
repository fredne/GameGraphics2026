#include "pch.h"
#include "Material.h"
#include "Shader/Shader.h"

namespace F
{
	void Material::Bind(ID3D11DeviceContext* context)
	{
		shader->Bind(context);
	}
	Shader* Material::GetShader() { return shader; }
	
	void Material::SetShader(Shader* shader) { this->shader = shader; }
}