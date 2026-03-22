#pragma once
#include "Debug/Debug.h"
#include "Resource.h"

namespace F
{
	class Resource;
	class ResourceArchive
	{
	private:
		std::unordered_map<std::string, std::shared_ptr<Resource>> archive;

		ResourceArchive() = default;
		ResourceArchive(const ResourceArchive&) = delete;
		ResourceArchive& operator=(const ResourceArchive&) = delete;
		ResourceArchive(ResourceArchive&&) = delete;
		ResourceArchive& operator=(ResourceArchive&&) = delete;

	public:
		static ResourceArchive& Get()
		{
			static ResourceArchive instance;
			return instance;
			
		}

		template<ResourceBase T>
		std::shared_ptr<T> Register(const std::string& key)
		{
			std::shared_ptr<T> item = archive[key];
			if (item == nullptr)
			{
				item = std::make_shared<T>();
				archive[key] = item;
				
				Debug::Log(std::format("Register resource {0} named {1}", typeid(T).name(), key));
			}
			else
			{
				Debug::Log(key + " already exits");
			}

			return item;
		}
		
		template<ResourceBase T>
		std::shared_ptr<T> Fetch(const std::string& key)
		{
			if (archive.contains(key)) return archive[key];
			Debug::Log(key + " do not exits");
			return nullptr;
		}
		

	};

}

