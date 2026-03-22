#pragma once
#include "pch.h"
#include <unordered_map>
#include <typeindex>
#include <Asset.h>

namespace F
{
	template<typename T>
	concept AssetBase = std::is_base_of_v<IAsset, T>&& requires(T t) { { t.Load() } -> std::same_as<Resource>; };

	class AssetManager
	{
	private:
		std::unordered_map <std::string, std::shared_ptr<IAsset>> assetUMap;
	
	public:
		void Initialize();

		template<AssetBase T>
		T* LoadAsset(const std::string& path, const AssetParam& param)
		{
			AssetKey key = { path, typeid(T) };

			auto it = assetUMap.find(path);
			if (it != assetUMap.end())
				return dynamic_cast<T*>(it->second);

			std::shared_ptr<T> asset = make_shared<T>(param);
			asset->Load();
			assetUMap[path] = asset;

			return asset;
		}
	};

}
