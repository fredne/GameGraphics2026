#pragma once

namespace F
{

	struct Key
	{
		friend class Keyboard;

	private:
		bool cur;
		bool prev;

		Key() : cur(false), prev(false) {}

	public:
		bool IsPressedNow() { return cur and !prev; }
		bool IsPressed() { return cur and prev; }
		bool IsReleased() { return !cur and prev; }

	};

	class Keyboard
	{
		friend class InputSystem;
		enum class KeyEnum
		{
			A, B, C, D, E, F, G, H, I, J, K, L, N,
			M, O, P, Q, R, S, T, U, V, W, X, Y, Z,
			Left, Right, Up, Down, Space, BackSpace,
			LShift, RShift, LCtrl, RCtrl, LAlt, RAlt,
			Tab, Caps, Esc, Enter,
			Dummy,
		};

	private:

		std::vector<Key*> keyList;

		Keyboard() = default;
		Keyboard(const Keyboard&) = delete;
		Keyboard& operator=(const Keyboard&) = delete;
		Keyboard(Keyboard&&) = delete;
		Keyboard& operator=(Keyboard&&) = delete;

		void Initialize();
		void Update();

	public:
		static Keyboard& Get()
		{
			static Keyboard instance;
			return instance;
		}

		Key aKey, bKey, cKey, dKey, eKey, fKey, gKey, hKey, iKey, jKey, kKey, lKey, nKey;
		Key mKey, oKey, pKey, qKey, rKey, sKey, tKey, uKey, vKey, wKey, xKey, yKey, zKey;
		Key left, right, up, down, space, backSpace, shift, ctrl, alt, tab, caps, esc, enter;

	};

}
