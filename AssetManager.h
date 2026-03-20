#pragma once
#include "pch.h"
#include <unordered_map>
#include <typeindex>

namespace F
{
	struct AssetKey
	{
		std::string path;
		std::type_index type;

		bool operator==(const AssetKey& other) const
		{
			return path == other.path && type == other.type;
		}
	};

	class Asset;
	template<typename T>
	concept AssetBase = std::is_base_of_v<Asset, T>&& requires(T t) { { t.Load() } -> std::same_as<void>; };

	class AssetManager
	{
	private:
		std::unordered_map <std::string, std::shared_ptr<Asset>> assetUMap;
	

	public:

		template<AssetBase T>
		T* LoadAsset(const std::string& path);
	};

	template<AssetBase T>
	inline T* AssetManager::LoadAsset(const std::string& path)
	{
		AssetKey key = { path, typeid(T) };

		auto it = assetUMap.find(path);
		if (it != assetUMap.end())
			return dynamic_cast<T*>(it->second);

		std::shared_ptr<T> asset = make_shared<T>();
		asset->Load();
		assetUMap[path] = asset;

		return asset;
	}

}
