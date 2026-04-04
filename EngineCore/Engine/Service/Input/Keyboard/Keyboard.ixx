#include "pch.h"
export module Keyboard;

export namespace F
{
	enum class KeyEnum
	{
		A, B, C, D, E, F, G, H, I, J, K, L, N,
		M, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		K1, K2, K3, K4, K5, K6, K7, K8, K9, K0,
		F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
		Left, Right, Up, Down, Space, BackSpace,
		LShift, RShift, LCtrl, RCtrl, LAlt, RAlt,
		Tab, Caps, Esc, Enter,

		Dummy,
	};

	struct Key
	{
		friend class Keyboard;

	private:
		bool cur;
		bool prev;
		KeyEnum keyEnum;

		Key() : cur(false), prev(false), keyEnum(KeyEnum::Dummy) {}

	public:
		bool IsPressedNow() { return cur and !prev; }
		bool IsPressed() { return cur and prev; }
		bool IsReleased() { return !cur and prev; }

	};

	class Keyboard
	{
		friend class InputSystem;
	private:

		std::vector<Key*> keyList;

		Keyboard() = default;
		Keyboard(const Keyboard&) = delete;
		Keyboard(Keyboard&&) = delete;
		Keyboard& operator=(const Keyboard&) = delete;
		Keyboard& operator=(Keyboard&&) = delete;

		void Initialize();
		void Update();

	public:
		static Keyboard& Get()
		{
			static Keyboard instance;
			return instance;
		}

		Key aKey, bKey, cKey, dKey, eKey, fKey, gKey, hKey, iKey, jKey, kKey, lKey, nKey,
			mKey, oKey, pKey, qKey, rKey, sKey, tKey, uKey, vKey, wKey, xKey, yKey, zKey,
			key1, key2, key3, key4, key5, key6, key7, key8, key9, key0, 
			f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12,
			left, right, up, down, space, backSpace, shiftL, shiftR, ctrlL, ctrlR, altL, altR,
			tab, caps, esc, enter;

	};

}
