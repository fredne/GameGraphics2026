#include "pch.h"
import Keyboard;

namespace F
{
	int keyArr[] =
	{
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'N',
		'M', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
		'1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
		VK_F1, VK_F2, VK_F3, VK_F4, VK_F5, VK_F6, VK_F7, VK_F8, VK_F9, VK_F10, VK_F11, VK_F12,
		VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN, VK_SPACE, VK_BACK,
		VK_LSHIFT, VK_RSHIFT, VK_LCONTROL, VK_RCONTROL, VK_LMENU, VK_RMENU,
		VK_TAB, VK_CAPITAL, VK_ESCAPE, VK_RETURN,

	};

	void Keyboard::Initialize()
	{
		keyList =
		{
			&aKey, &bKey, &cKey, &dKey, &eKey, &fKey, &gKey, &hKey, &iKey, &jKey, &kKey, &lKey, &nKey,
			&mKey, &oKey, &pKey, &qKey, &rKey, &sKey, &tKey, &uKey, &vKey, &wKey, &xKey, &yKey, &zKey,
			&key1, &key2, &key3, &key4, &key5, &key6, &key7, &key8, &key9, &key0,
			&f1, &f2, &f3, &f4, &f5, &f6, &f7, &f8, &f9, &f10, &f11, &f12,
			&left, &right, &up, &down, &space, &backSpace, &shiftL, &shiftR, &ctrlL, &ctrlR, &altL, &altR,
			&tab, &caps, &esc, &enter,
		};

		for (size_t i = 0; i < keyList.size(); ++i)
		{
			keyList[i]->keyEnum = static_cast<KeyEnum>(i);
		}
	}

	void Keyboard::Update()
	{
		for (int i = 0; i < keyList.size(); ++i)
		{
			bool isKeyPress = GetAsyncKeyState(keyArr[i]) && 0x8000;
			keyList[i]->prev = keyList[i]->cur;
			keyList[i]->cur = isKeyPress;
		}
	}

}