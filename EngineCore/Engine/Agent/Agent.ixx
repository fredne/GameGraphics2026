#include "pch.h"
export module Agent;
import Module;

export namespace F
{
	class Module;
	class Agent
	{
	private:
		std::vector<std::unique_ptr<Module>> moduleList;

	public:
		Agent();
		void Initialize();
		void Update(float dt);
		void Render(ID3D11DeviceContext* context);
		void Release();

		template<ModuleBase T>
		T* AddModule()
		{
			std::unique_ptr<T> mod = std::make_unique<T>();
			mod->agent = this;
			T* modRaw = mod.get();
			moduleList.push_back(std::move(mod));
			return modRaw;
		}

		template<ModuleBase T>
		T* GetModule()
		{
			for (auto& mod : moduleList)
			{
				if (dynamic_cast<T*>(mod.get()))
				{
					return dynamic_cast<T*>(mod.get());
				}
			}

			std::cerr << typeid(T).name() << " do not exist" << std::endl;

			return nullptr;

		}

	};

}