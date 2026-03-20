#include "pch.h"
#include "Shader.h"
#include "DX.h"
#include "Debug.h"

namespace F
{
	Shader::Shader(std::wstring vsFile, std::wstring psFile)
	{
		ID3DBlob* vsBlob, * psBlob, * errVBlob, * errPBlob = nullptr;
		D3DCompileFromFile(vsFile.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "VSMain", "vs_5_0", 0, 0, &vsBlob, &errVBlob);
		D3DCompileFromFile(psFile.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PSMain", "ps_5_0", 0, 0, &psBlob, &errPBlob);

		if (errVBlob)
		{
			std::string msg((char*)errVBlob->GetBufferPointer(), errVBlob->GetBufferSize());
			Debug::Log("Vertex Shader Error: %s", msg.c_str());
		}
		if (errPBlob)
		{
			std::string msg((char*)errPBlob->GetBufferPointer(), errPBlob->GetBufferSize());
			Debug::Log("Pixel Shader Error: %s", msg.c_str());
		}

		DX::device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, &vertexShader);
		DX::device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, &pixelShader);
	
		std::vector<D3D11_INPUT_ELEMENT_DESC> layoutDescs =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		DX::device->CreateInputLayout(layoutDescs.data(), (UINT)layoutDescs.size(), vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &inputLayout);

		vsBlob->Release();
		psBlob->Release();
		if (errVBlob) errVBlob->Release();
		if (errPBlob) errPBlob->Release();
	}

	Shader::~Shader()
	{
		if (inputLayout) inputLayout->Release();
		if (vertexShader) vertexShader->Release();
		if (pixelShader) pixelShader->Release();
	}

	void Shader::Bind(ID3D11DeviceContext* context)
	{
		context->IASetInputLayout(inputLayout);
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		context->VSSetShader(vertexShader, nullptr, 0);
		context->PSSetShader(pixelShader, nullptr, 0);
	}
}


