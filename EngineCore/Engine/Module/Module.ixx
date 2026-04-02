#include "pch.h"
export module Module;

export namespace F
{
	class RenderContext;
	class Agent;
	class Module
	{
	private:
		friend class Agent;

	protected:
		Agent* agent;

	public:
		virtual ~Module();
		virtual void Update(float dt) = 0;
		virtual void Render(ID3D11DeviceContext* context);

	};

}
;