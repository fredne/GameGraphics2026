#pragma once
#include "Common.h"
#include "Resource.h"

namespace F
{
	class Shader : public Resource
	{
	private:
		ComPtr<ID3D11InputLayout> inputLayout = nullptr;
		ComPtr<ID3D11VertexShader> vertexShader = nullptr;
		ComPtr<ID3D11PixelShader> pixelShader = nullptr;

	public:
		Shader(const std::wstring& vsFile, const std::wstring& psFile);
		virtual ~Shader();

		std::vector<char> LoadCSO(const std::wstring& filename);
		void LoadHLSL(const std::wstring& vsFile, const std::wstring& psFile);

		void Bind(ID3D11DeviceContext* context);

	};

}
