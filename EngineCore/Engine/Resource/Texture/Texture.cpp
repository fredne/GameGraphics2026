#include "pch.h"
#include "DirectXTex.h"
import Texture;

namespace F
{
	Texture::Texture() : 
		dxSRV(nullptr), width(0), height(0)
	{ }
	Texture::~Texture()
	{ }

	bool Texture::Load(ID3D11Device* device, const std::wstring& filepath)
	{
		DirectX::TexMetadata tmd;
		DirectX::ScratchImage simg;
		HRESULT hr;
		if (filepath.rfind(L".dds") != std::string::npos)
			hr = DirectX::LoadFromDDSFile(filepath.c_str(), DirectX::DDS_FLAGS_NONE, &tmd, simg);
		else
			hr = DirectX::LoadFromWICFile(filepath.c_str(), DirectX::WIC_FLAGS_NONE, &tmd, simg);

		if (FAILED(hr)) return false;

		hr = DirectX::CreateShaderResourceView(device, simg.GetImages(), simg.GetImageCount(), tmd, dxSRV.GetAddressOf());
		width = tmd.width;
		height = tmd.height;

		return SUCCEEDED(hr);

	}
	void Texture::Bind(ID3D11DeviceContext* context, uint32_t slot)
	{
		context->PSSetShaderResources(slot, 1, dxSRV.GetAddressOf());
	}
}