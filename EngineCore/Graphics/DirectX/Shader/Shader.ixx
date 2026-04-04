#include "pch.h"
export module Shader;

export namespace F
{
	class Shader
	{
	private:
		ComPtr<ID3D11InputLayout> inputLayout = nullptr;
		ComPtr<ID3D11VertexShader> vertexShader = nullptr;
		ComPtr<ID3D11PixelShader> pixelShader = nullptr;

	public:
		Shader();
		virtual ~Shader();

		void Initialize(const std::wstring& vsFile, const std::wstring& psFile);
		void LoadHLSL(const std::wstring& vsFile, const std::wstring& psFile);
		bool LoadCSO(const std::wstring& vsFile, const std::wstring& psFile);
		std::vector<char> GetCSOData(const std::string& fileName);

		void Bind(ID3D11DeviceContext* context);

	};

}
