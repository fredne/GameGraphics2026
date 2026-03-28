#include "pch.h"
import Material;
import Shader;

namespace F
{
	void Material::Bind(ID3D11DeviceContext* context)
	{
		shader->Bind(context);
	}
	Shader* Material::GetShader() { return shader; }
	
	void Material::SetShader(Shader* shader) { this->shader = shader; }
}