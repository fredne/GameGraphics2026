#include "pch.h"
import ConstantBuffer;
import DX;
import Debug;

namespace F
{
	ConstantBuffer0::ConstantBuffer0()
	{
		D3D11_BUFFER_DESC desc = {};
		desc.ByteWidth = sizeof(CBuffer0);
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		HRESULT hr = DX::Get().device->CreateBuffer(&desc, 0, &buffer);
		if (FAILED(hr))
		{
			Debug::Log("Constant Buffer 생성 실패");
		}
	}
	void ConstantBuffer0::UpdateBuffer(ID3D11DeviceContext* context, const CBuffer0& cb0)
	{
		data = cb0;
		context->UpdateSubresource(buffer.Get(), 0, nullptr, &data, 0, 0);
	}

	void ConstantBuffer0::Bind(ID3D11DeviceContext* context)
	{
		context->VSSetConstantBuffers(0, 1, buffer.GetAddressOf());
	}

	//ComPtr<ID3D11Buffer>& ConstantBuffer0::GetBuffer() { return buffer; }
	ID3D11Buffer* ConstantBuffer0::GetBufferRaw() { return buffer.Get(); }

}