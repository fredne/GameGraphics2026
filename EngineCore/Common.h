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

	struct Vector2
	{
		float x, y;
		float* GetData() { return &x; }

		Vector2() : x(0), y(0) {}
		Vector2(float v) : x(v), y(v) {}
		Vector2(float x, float y) : x(x), y(y) {}

	};
	struct Vector3
	{
		float x, y, z;
		float* GetData() { return &x; }

		Vector3() : x(0), y(0), z(0) {}
		Vector3(float v) : x(v), y(v), z(v) {}
		Vector3(float x, float y, float z) : x(x), y(y), z(z) {}


	};

	struct Vertex {
		Vector3 position;
		Color color;

		Vertex(float x, float y, float z, float r, float g, float b, float a) :
			position(x, y, z), color(r, g, b, a)
		{
		}
	};

	class Resource;
	template<typename T>
	concept ResourceBase = std::is_base_of_v<Resource, T>;
	
	class AssetParam;
	template<typename T>
	concept AssetParamBase = std::is_base_of_v<AssetParam, T>;

	class Module;
	template<typename T>
	concept ModuleBase = std::is_base_of_v<Module, T>;
}
