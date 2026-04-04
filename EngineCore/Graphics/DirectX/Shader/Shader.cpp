#include "pch.h"
import DX;
import File;
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
	Shader::Shader()
	{ }

	Shader::~Shader()
	{
		//if (inputLayout) inputLayout->Release();
		//if (vertexShader) vertexShader->Release();
		//if (pixelShader) pixelShader->Release();
	}

	void Shader::Initialize(const std::wstring& vsFile, const std::wstring& psFile)
	{
		try
		{
			if (!LoadCSO(vsFile, psFile))
			{
				LoadHLSL(vsFile, psFile);
			}

		}
		catch (const std::runtime_error& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}

	void Shader::LoadHLSL(const std::wstring& vsFile, const std::wstring& psFile)
	{
		std::wstring exeFolder = GetExeFolder();
		std::ifstream file(exeFolder + vsFile, std::ios::binary | std::ios::ate);
		if (!file)
			throw std::runtime_error(std::format("Vertex Shader do not exists: {0}", File::WStringToString(exeFolder + vsFile)));
		file.close();
		
		file.open(exeFolder + psFile, std::ios::binary | std::ios::ate);
		if (!file)
			throw std::runtime_error(std::format("Pixel Shader do not exists: {}", File::WStringToString(exeFolder + psFile)));
		file.close();

		ID3DBlob* vsBlob, * psBlob, * errVBlob, * errPBlob = nullptr;
		HRESULT hr = D3DCompileFromFile(vsFile.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "VSMain", "vs_5_0", D3DCOMPILE_DEBUG, 0, &vsBlob, &errVBlob);
		if (FAILED(hr) and errVBlob)
		{
			char* compileErrors = (char*)(errVBlob->GetBufferPointer());
			throw std::runtime_error(std::format("Vertex Shader Compile Error: {}", compileErrors));
			errVBlob->Release();
		}
		
		hr = D3DCompileFromFile(psFile.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PSMain", "ps_5_0", D3DCOMPILE_DEBUG, 0, &psBlob, &errPBlob);
		if (FAILED(hr) and errPBlob)
		{
			char* compileErrors = (char*)(errPBlob->GetBufferPointer());
			throw std::runtime_error(std::format("Pixel Shader Compile Error: {}", compileErrors));
			errPBlob->Release();
		}

		DX::Get().device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, &vertexShader);
		DX::Get().device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, &pixelShader);

		std::vector<D3D11_INPUT_ELEMENT_DESC> layoutDescs =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		DX::Get().device->CreateInputLayout(layoutDescs.data(), (UINT)layoutDescs.size(), vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &inputLayout);

		vsBlob->Release();
		psBlob->Release();
		if (errVBlob) errVBlob->Release();
		if (errPBlob) errPBlob->Release();
	}

	bool Shader::LoadCSO(const std::wstring& vsFile, const std::wstring& psFile)
	{
		std::wstring exeFolder = GetExeFolder();
		std::vector<char> vsData;
		std::vector<char> psData;
		try
		{
			vsData = GetCSOData(File::WStringToString(exeFolder + vsFile));
			psData = GetCSOData(File::WStringToString(exeFolder + psFile));
		}
		catch (const std::runtime_error& runTimeError)
		{
			OutputDebugStringA(runTimeError.what());
			return false;
		}

		DX::Get().device->CreateVertexShader(vsData.data(), vsData.size(), nullptr, &vertexShader);
		DX::Get().device->CreatePixelShader(psData.data(), psData.size(), nullptr, &pixelShader);

		std::vector<D3D11_INPUT_ELEMENT_DESC> layoutDescs =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		DX::Get().device->CreateInputLayout(layoutDescs.data(), (UINT)layoutDescs.size(), vsData.data(), vsData.size(), &inputLayout);

		return true;
	}

	 std::vector<char> Shader::GetCSOData(const std::string& fileName)
	{
		std::ifstream file(fileName, std::ios::binary | std::ios::ate);
		if (!file)
			throw std::runtime_error("Failed to open CSO file: " + fileName);
		std::streamsize size = file.tellg();
		if (size <= 0)
			throw std::runtime_error("CSO file is empty: " + fileName);
		file.seekg(0, std::ios::beg);
		std::vector<char> buffer(static_cast<size_t>(size));
		if (!file.read(buffer.data(), size))
			throw std::runtime_error("Failed to read CSO file: " + fileName);
		file.close();

		return buffer;

	}

	void Shader::Bind(ID3D11DeviceContext* context)
	{
		context->IASetInputLayout(inputLayout.Get());
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		context->VSSetShader(vertexShader.Get(), nullptr, 0);
		context->PSSetShader(pixelShader.Get(), nullptr, 0);
	}

}


