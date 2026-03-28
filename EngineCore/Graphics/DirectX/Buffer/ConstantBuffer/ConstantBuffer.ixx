#include "pch.h"
export module ConstantBuffer;

export struct CBuffer0
{
	DirectX::XMFLOAT4X4 MVP;

	CBuffer0() {}
	CBuffer0(const CBuffer0& other)
	{
		MVP = other.MVP;
	}

};

export namespace F
{
	class ConstantBuffer0
	{
	private:
		ComPtr<ID3D11Buffer> buffer;

	public:
		CBuffer0 data;

		ConstantBuffer0();

		//void StoreData(XMMATRIX mvp)
		//{
		//	XMStoreFloat4x4(&MVP, mvp);
		//}

		void UpdateBuffer(ID3D11DeviceContext* context, const CBuffer0& cb0);
		void Bind(ID3D11DeviceContext* context);

		//ComPtr<ID3D11Buffer>& GetBuffer();
		ID3D11Buffer* GetBufferRaw();
	};



}