#include "pch.h"
export module World;

export namespace F
{
	class Agent;
	class World
	{
	private:
		std::vector<std::unique_ptr<Agent>> agentList;

	public:
		virtual ~World();

		virtual void Enter();
		virtual void Exit();

		void Initialize();
		void Release();
		void Update(float dt);
		void Render(ID3D11DeviceContext* context);
		Agent* AddAgent(std::unique_ptr<Agent> agent);


	};

}