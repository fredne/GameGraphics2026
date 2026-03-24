#include "pch.h"
export module Archive;
import Debug;

export namespace F
{
	template<typename T,typename U>
	class Archive
	{
		Archive(const Archive&) = delete;
		Archive& operator=(const Archive&) = delete;
		Archive(Archive&&) = delete;
		Archive& operator=(Archive&&) = delete;

	protected:
		std::unordered_map<std::string, std::unique_ptr<U>> archive;
		Archive() = default;

	public:
		static T& Get()
		{
			static T instance;
			return instance;
		}
		virtual ~Archive() {}

		virtual void Initialize() { };
		virtual void Release();

		template<typename UBase>
		requires std::is_base_of_v<U, UBase>
		UBase* Register(const std::string& key)
		{
			UBase* item = archive[key].get();
			if (item == nullptr)
			{
				archive[key] = std::make_unique<U>();
				item = archive[key].get();
				Debug::Log(std::format("Register {0} named {1}", typeid(UBase).name(), key));
			}
			else
			{
				Debug::Log(key + " already exits");
			}

			return item;
		}

		template<typename UBase>
		requires std::is_base_of_v<U, UBase>
		UBase* Fetch(const std::string& key)
		{
			if (archive.contains(key)) return dynamic_cast<UBase*>(archive[key].get());
			Debug::Log(key + " do not exits");
			return nullptr;
		}

	};

	template<typename T, typename U>
	void Archive<T, U>::Release()
	{
		archive.clear();
	}
}