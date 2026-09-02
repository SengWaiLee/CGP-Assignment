#include <Windows.h>
#include <iostream>
#define WIN32_LEAN_AND_MEAN
#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

class WindowManager
{
public:
	static HWND g_hWnd;
	WNDCLASS wndClass;
	static CONST int ScreenWidth = 1920;
	static CONST int ScreenHeight = 1080;
	WindowManager();
	~WindowManager();
	void CleanUpWindow();
	bool WindowIsRunning();
};
#endif