#pragma once
#include <typeindex>
#include <fstream>

namespace F
{
	struct AssetParam { };
	struct IAsset { };
	struct AssetKey
	{
		std::string path;
		std::type_index type;

		bool operator==(const AssetKey& other) const
		{
			return path == other.path && type == other.type;
		}
	};

	class Resource;

	template<ResourceBase T>
	class Asset : IAsset
	{
	private:
		AssetParam param;

	public:

		Asset<T>(const AssetParam& param) : param(param) { }
		~Asset<T>() { }

		virtual T* Load(const std::wstring& path) = 0;
		virtual void Create(const std::wstring& path) = 0;

		template<AssetParamBase U>
		U* GetParam() { return static_cast<U*>(&param); }

	};



}
