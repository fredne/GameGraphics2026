#include "pch.h"
export module Texture;

export namespace F
{
	class Texture
	{
	private:
		ComPtr<ID3D11ShaderResourceView> dxSRV;
		uint32_t width;
		uint32_t height;

	public:
		Texture();
		~Texture();

		bool Load(ID3D11Device* device, const std::wstring& filepath);
		void Bind(ID3D11DeviceContext* context, uint32_t slot = 0);

		ID3D11ShaderResourceView* GetSRV() const { return dxSRV.Get(); }
		uint32_t GetWidth() const { return width; }
		uint32_t GetHeight() const { return height; }

	};

}