#pragma once

namespace F
{
	enum class Key
	{
		A, B, C, D, E, F, G, H, I, J, K, L, N,
		M, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		Left, Right, Up, Down, Space, BackSpace,
		Shift, Ctrl, Alt, Tab, Caps, Esc, Enter,
		Dummy,
	};

	struct KeyState
	{
		bool curr;
		bool prev;
	};

	namespace F
	{
		class InputSystem
		{
		private:
			InputSystem();

			std::vector<KeyState> keyList;

		public:
			static InputSystem& Instance;

			void Update();


		};

	}

}
