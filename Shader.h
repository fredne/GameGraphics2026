#pragma once
#include "Common.h"

namespace F
{
	class Shader
	{
	private:
		ID3D11InputLayout* inputLayout = nullptr;
		ID3D11VertexShader* vertexShader = nullptr;
		ID3D11PixelShader* pixelShader = nullptr;

	public:
		Shader(std::wstring vsFile, std::wstring psFile);
		~Shader();

		void Bind(ID3D11DeviceContext* context);

	};

}
