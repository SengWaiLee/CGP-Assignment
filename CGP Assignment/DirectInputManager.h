#pragma once
#include <dinput.h>
#include "WindowManager.h"
class DirectInputManager
{
public:
	LPDIRECTINPUTDEVICE8  dInputKeyboardDevice = NULL;
	LPDIRECTINPUTDEVICE8  dInputMouseDevice = NULL;
	static BYTE diKeys[256];
	static DIMOUSESTATE mouseState;
	LPDIRECTINPUT8 dInput = NULL;

	DirectInputManager();
	~DirectInputManager();
	void CleanUpDirectInput();
	void GettingInput();
};