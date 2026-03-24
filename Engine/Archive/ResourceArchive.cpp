#include "pch.h"
#include "ResourceArchive.h"
#include "Shader/Shader.h"

namespace F
{
	void ResourceArchive::Initialize()
	{
		// Shader
		auto defaultShader = std::make_unique<Shader>(L"VertexShader.cso", L"PixelShader.cso");
		archive["DefaultShader"] = std::move(defaultShader);

	}


}