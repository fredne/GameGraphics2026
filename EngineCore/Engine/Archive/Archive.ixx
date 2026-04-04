#include "pch.h"
export module Archive;

export namespace F
{
	template<typename TSelf, typename TItem>
	class Archive
	{
		Archive(const Archive&) = delete;
		Archive(Archive&&) = delete;
		Archive& operator=(const Archive&) = delete;
		Archive& operator=(Archive&&) = delete;

	protected:
		std::unordered_map<std::string, std::unique_ptr<TItem>> archive;
		Archive() = default;

	public:
		static TSelf& Get()
		{
			static TSelf instance;
			return instance;
		}
		virtual ~Archive() { };

		virtual void Initialize() { };
		virtual void Release();

		template<typename TItemBase>
		requires std::derived_from<TItemBase, TItem>
		TItemBase* Register(const std::string& key)
		{
			TItemBase* item = dynamic_cast<TItemBase*>(archive[key].get());
			if (item == nullptr)
			{
				archive[key] = std::make_unique<TItemBase>();
				item = dynamic_cast<TItemBase*>(archive[key].get());
			#ifdef _DEBUG
				std::cout << std::format("[{}] Register item with key: {}\n", typeid(TSelf).name(), key);
			#endif
				
			}

			return item;
		}

		template<typename TItemBase>
		requires std::derived_from<TItemBase, TItem>
		TItemBase* Fetch(const std::string& key)
		{
			if (archive.contains(key)) 
				return dynamic_cast<TItemBase*>(archive[key].get());
		#ifdef _DEBUG
			std::cout << std::format("[{}] \033[31m[Error] \033[0mFailed to fetch item with key: {}\n", typeid(TSelf).name(), key);
		#endif 

			return nullptr;
		}

	};

	template<typename TSelf, typename TItem>
	void Archive<TSelf, TItem>::Release()
	{
		archive.clear();
	}
}