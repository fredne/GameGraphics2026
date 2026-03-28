#include "pch.h"	
import ShaderArchive;

namespace F
{
	void ShaderArchive::Initialize()
	{
		// Shader
		auto defaultShader = std::make_unique<Shader>(L"VertexShader.cso", L"PixelShader.cso");
		archive["DefaultShader"] = std::move(defaultShader);
	}
}