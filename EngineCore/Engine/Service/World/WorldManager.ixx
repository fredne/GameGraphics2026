#include "pch.h"
export module WorldManager;
import WorldArchive;
import World;

export namespace F
{
	class World;
	class WorldManager
	{
	private:
		World* currentWorld;

		WorldManager() = default;
		WorldManager(const WorldManager&) = delete;
		WorldManager(WorldManager&&) = delete;
		WorldManager& operator=(const WorldManager&) = delete;
		WorldManager& operator=(WorldManager&&) = delete;

	public:
		~WorldManager() {};
		static WorldManager& Get()
		{
			static WorldManager instance;
			return instance;
		}

		void Initialize();
		void Release();
		void Update(float dt);
		void Render(ID3D11DeviceContext* context);

		template<typename WorldBase>
		requires std::derived_from<WorldBase, World>
		void LoadWorld(const std::string& name)
		{
			if (currentWorld)
				currentWorld->Exit();

			WorldBase* world = dynamic_cast<WorldBase*>(WorldArchive::Get().Fetch<World>(name));

			if (world)
			{
				currentWorld = world;
				currentWorld->Enter();
				currentWorld->Initialize();
				return;
			}

			std::cout << std::format("[{}] \033[31m[Error] \033[0mFailed to load world with name: {}\n", typeid(WorldArchive).name(), name);

		}
	};
}