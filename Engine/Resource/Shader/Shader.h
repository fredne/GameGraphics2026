#pragma once
#include "Common.h"
#include "Resource.h"

namespace F
{
	class Shader : Resource
	{
	private:
		ID3D11InputLayout* inputLayout = nullptr;
		ID3D11VertexShader* vertexShader = nullptr;
		ID3D11PixelShader* pixelShader = nullptr;

	public:
		Shader(const std::wstring& vsFile, const std::wstring& psFile);
		~Shader();

		std::vector<char> LoadCSO(const std::wstring& filename);
		void LoadHLSL(const std::wstring& vsFile, const std::wstring& psFile);

		void Bind(ID3D11DeviceContext* context);



	};

}
