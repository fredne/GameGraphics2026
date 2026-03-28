#include "pch.h"
import Keyboard;

namespace F
{
	int keyArr[] =
	{
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'N',
		'M', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
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
			&left, &right, &up, &down, &space, &backSpace, &shift, &ctrl, &alt, &tab, &caps, &esc, &enter,
		};
	}

	void Keyboard::Update()
	{
		for (int i = 0; i < keyList.size(); ++i)
		{
			bool isKeyPress = GetAsyncKeyState(keyArr[i]) && 0x8000;
			if (isKeyPress)
			{
				int a = 1;
			}
			keyList[i]->prev = keyList[i]->cur;
			keyList[i]->cur = isKeyPress;
		}
	}

}