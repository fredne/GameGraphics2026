#include "pch.h"
#include "Shader.h"
#include "DX.h"
#include "Debug/Debug.h"
#include <fstream>

std::wstring GetExeFolder()
{
	wchar_t buffer[MAX_PATH];
	GetModuleFileNameW(nullptr, buffer, MAX_PATH); // 현재 실행 모듈 경로
	std::wstring path(buffer);

	// 마지막 '\' 기준으로 폴더만 추출
	size_t pos = path.find_last_of(L"\\/");
	if (pos != std::wstring::npos)
		path = path.substr(0, pos + 1); // 폴더 경로 끝에 '\' 포함

	pos = 0;
	while ((pos = path.find(L"\\", pos)) != std::wstring::npos)
	{
		path.replace(pos, 1, L"/");
		pos++;
	}
	return path;
}

namespace F
{
	Shader::Shader(const std::wstring& vsFile, const std::wstring& psFile)
	{
		std::wstring exeFolder = GetExeFolder();
		auto vsData = LoadCSO(exeFolder + vsFile);
		auto psData = LoadCSO(exeFolder + psFile);

		DX::device->CreateVertexShader(vsData.data(), vsData.size(), nullptr, &vertexShader);
		DX::device->CreatePixelShader(psData.data(), psData.size(), nullptr, &pixelShader);

		std::vector<D3D11_INPUT_ELEMENT_DESC> layoutDescs =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		DX::device->CreateInputLayout(layoutDescs.data(), (UINT)layoutDescs.size(), vsData.data(), vsData.size(), &inputLayout);

	}

	std::vector<char> Shader::LoadCSO(const std::wstring& filename)
	{
		std::ifstream file(filename, std::ios::binary | std::ios::ate);
		if (!file)
			throw std::runtime_error("Failed to open CSO file");

		std::streamsize size = file.tellg();
		if (size <= 0)
			throw std::runtime_error("CSO file is empty");

		file.seekg(0, std::ios::beg);
		std::vector<char> buffer(static_cast<size_t>(size));
		if (!file.read(buffer.data(), size))
			throw std::runtime_error("Failed to read CSO file");

		return buffer;
	}

	Shader::~Shader()
	{
		if (inputLayout) inputLayout->Release();
		if (vertexShader) vertexShader->Release();
		if (pixelShader) pixelShader->Release();
	}

	void Shader::LoadHLSL(const std::wstring& vsFile, const std::wstring& psFile)
	{
		ID3DBlob* vsBlob, * psBlob, * errVBlob, * errPBlob = nullptr;
		D3DCompileFromFile(vsFile.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "VSMain", "vs_5_0", 0, 0, &vsBlob, &errVBlob);
		D3DCompileFromFile(psFile.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PSMain", "ps_5_0", 0, 0, &psBlob, &errPBlob);

		if (errVBlob)
		{
			std::string msg((char*)errVBlob->GetBufferPointer(), errVBlob->GetBufferSize());
			Debug::Log("Vertex Shader Error: " + msg);
		}
		if (errPBlob)
		{
			std::string msg((char*)errPBlob->GetBufferPointer(), errPBlob->GetBufferSize());
			Debug::Log("Pixel Shader Error: " + msg);
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

	void Shader::Bind(ID3D11DeviceContext* context)
	{
		context->IASetInputLayout(inputLayout);
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		context->VSSetShader(vertexShader, nullptr, 0);
		context->PSSetShader(pixelShader, nullptr, 0);
	}

}


