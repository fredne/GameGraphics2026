#include "pch.h"
export module ConstantBuffer;

export namespace F
{
	template<typename CBufferN>
	requires std::is_base_of_v<CBuffer, CBufferN>
	class ConstantBuffer
	{
	private:
		ComPtr<ID3D11Buffer> buffer;

	public:
		CBufferN data;

		ConstantBuffer(ID3D11Device* device)
		{
			D3D11_BUFFER_DESC desc = {};
			desc.ByteWidth = sizeof(CBufferN);
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			HRESULT hr = device->CreateBuffer(&desc, 0, &buffer);
			if (FAILED(hr))
			{
				throw("Constant Buffer 생성 실패");
			}
		}

		void BindVS(ID3D11DeviceContext* context, uint32_t slot)
		{
			context->UpdateSubresource(buffer.Get(), 0, nullptr, &data, 0, 0);
			context->VSSetConstantBuffers(slot, 1, buffer.GetAddressOf());
		}
		void BindPS(ID3D11DeviceContext* context, uint32_t slot)
		{
			context->UpdateSubresource(buffer.Get(), 0, nullptr, &data, 0, 0);
			context->PSSetConstantBuffers(slot, 1, buffer.GetAddressOf());
		}

		ID3D11Buffer* GetBufferRaw() { return buffer.Get(); }

	};



}