#include "pch.h"	
import ShaderArchive;

namespace F
{
	void ShaderArchive::Initialize()
	{
		// Shader
		Register<Shader>("DefaultShader")->Initialize(L"VertexShader.cso", L"PixelShader.cso");

	}
}