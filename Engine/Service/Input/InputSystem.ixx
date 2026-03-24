#include "pch.h"
export module InputSystem;

export namespace F
{
	class InputSystem
	{
	private:
		InputSystem() = default;

	public:
		static InputSystem& Get()
		{
			static InputSystem instance;
			return instance;
		}

		void Initialize();
		void Update();


	};


}
