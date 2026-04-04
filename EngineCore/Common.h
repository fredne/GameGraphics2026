#pragma once

namespace F
{
	struct Color
	{
		float r, g, b, a;
		float* GetData() { return &r; }

		Color() : r(0), g(0), b(0), a(1) {}
		Color(float v) : r(v), g(v), b(v), a(1) {}
		Color(float r, float g, float b) : r(r), g(g), b(b), a(1) {}
		Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}
	};

	template<typename T>
	requires std::is_arithmetic_v<T>
	struct Vector2 
	{
		T x, y;	
		T* GetData() { return &x; }

		Vector2() : x(0), y(0) {}
		Vector2(T v) : x(v), y(v) {}
		Vector2(T x, T y) : x(x), y(y) {}

	};

	template<>
	struct Vector2<float> : public DirectX::XMFLOAT2
	{
		Vector2() : XMFLOAT2(0, 0) {}
		Vector2(float v) : XMFLOAT2(v, v) {}
		Vector2(float x, float y) : XMFLOAT2(x, y) {}

		Vector2 operator+(const Vector2& other) const
		{
			XMVECTOR v1 = XMLoadFloat2(this);
			XMVECTOR v2 = XMLoadFloat2(&other);
			XMVECTOR result = XMVectorAdd(v1, v2);
			Vector2 res;
			XMStoreFloat2(&res, result);
			return res;
		}
	};

	struct Vector3 : public DirectX::XMFLOAT3
	{
		Vector3() : XMFLOAT3(0, 0, 0) {}
		Vector3(float v) : XMFLOAT3(v, v, v) {}
		Vector3(float x, float y, float z) : XMFLOAT3(x, y, z) {}

		Vector3 operator+(const Vector3& other) const
		{
			XMVECTOR v1 = XMLoadFloat3(this);
			XMVECTOR v2 = XMLoadFloat3(&other);
			Vector3 result;
			XMStoreFloat3(&result, XMVectorAdd(v1, v2));
			return result;
		}
		Vector3 operator*(float v) const
		{
			XMVECTOR v1 = XMLoadFloat3(this);
			XMVECTOR vRes = XMVectorScale(v1, v);
			Vector3 result;
			XMStoreFloat3(&result, vRes);
			return result;
		}
		Vector3 operator/(float v) const
		{
			float invV = 1.f / v;
			XMVECTOR v1 = XMLoadFloat3(this);
			Vector3 result;
			XMStoreFloat3(&result, XMVectorScale(v1, invV));
			return result;
		}

		Vector3& operator+=(const Vector3& other)
		{
			XMVECTOR v1 = XMLoadFloat3(this);
			XMVECTOR v2 = XMLoadFloat3(&other);
			XMStoreFloat3(this, XMVectorAdd(v1, v2));
			return *this;
		}
		Vector3& operator*=(float v)
		{
			XMVECTOR v1 = XMLoadFloat3(this);
			XMStoreFloat3(this, XMVectorScale(v1, v));
			return *this;
		}

		void Normalize()
		{
			XMVECTOR v = XMLoadFloat3(this);
			XMStoreFloat3(this, XMVector3Normalize(v));
		}
		Vector3 Normalized() const
		{
			XMVECTOR v = XMLoadFloat3(this);
			Vector3 result;
			XMStoreFloat3(&result, XMVector3Normalize(v));
			return result;
		}

	};

	struct Vertex 
	{
		Vector3 position;
		Vector2<float> uv;

		Vertex(float x, float y, float z, float u, float v) :
			position(x, y, z), uv(u, v)
		{ }
	};


	struct CBuffer {};
	struct CBuffer0 : public CBuffer
	{
		DirectX::XMFLOAT4X4 MVP;

		CBuffer0() : MVP() {}
		CBuffer0(const CBuffer0& other) : MVP(other.MVP) {}
	};
	struct CBuffer3 : public CBuffer
	{
		Color color;

		CBuffer3() : color(0, 0, 0, 0) {}
		CBuffer3(const CBuffer3& other) : color(other.color) {}
		CBuffer3(float v) : color(v, v, v) {}
		CBuffer3(float r, float g, float b) : color(r, g, b) {}
		CBuffer3(float r, float g, float b, float a) : color(r, g, b, a) {}

	};

	class Module;
	template<typename T>
	concept ModuleBase = std::derived_from<T, Module>;

}
