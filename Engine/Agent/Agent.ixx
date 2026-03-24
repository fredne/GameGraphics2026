#include "pch.h"
export module Agent;

export namespace F
{
	class Module;
	class Agent
	{
	private:
		std::vector<std::unique_ptr<Module>> moduleList;

	public:
		void AA();
		template<ModuleBase T>
		T* AddModule()
		{
			std::unique_ptr<T> mod = std::make_unique<T>();
			T* rm = mod.get();
			moduleList.push_back(std::move(mod));
		}

	};

}