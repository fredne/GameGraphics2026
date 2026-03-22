#include "pch.h"
#include "ShaderAsset.h"

namespace F
{
	ShaderAsset::ShaderAsset(const ShaderAssetParam& param) : Asset<Shader>(param)
	{
	}

	Shader* ShaderAsset::Load(const std::wstring& path)
	{
		ShaderAssetParam* param = GetParam<ShaderAssetParam>();
		return new Shader(param->vsFile, param->psFile);
	}

	void ShaderAsset::Create(const std::wstring& path)
	{
		ShaderAssetParam* param = GetParam<ShaderAssetParam>();
		std::ofstream file(path, std::ios::binary);
		file.write((char*)&param, sizeof(param));
		
	}






}

