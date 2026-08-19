#include "WindowManager.h"
#include <iostream>
using namespace std;
HWND WindowManager::g_hWnd;
CONST int WindowManager::ScreenWidth;
CONST int WindowManager::ScreenHeight;
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		//	The message is post when we destroy the window.
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_ESCAPE:
			PostQuitMessage(0);
			cout << "quit game" << endl;
			break;
		}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


WindowManager::WindowManager()
{

	ZeroMemory(&wndClass, sizeof(wndClass));
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hInstance = GetModuleHandle(NULL);	//	GetModuleHandle(NULL);
	wndClass.lpfnWndProc = WindowProcedure;
	wndClass.lpszClassName = "My Window";
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	//Register Window
	RegisterClass(&wndClass);

	g_hWnd = CreateWindowEx(0, wndClass.lpszClassName, "Game Windows", WS_OVERLAPPEDWINDOW, 0, 0, ScreenWidth, ScreenHeight, NULL, NULL, GetModuleHandle(NULL), NULL);
	ShowWindow(g_hWnd, 1);
}

WindowManager::~WindowManager()
{}



void WindowManager::CleanUpWindow()
{
	UnregisterClass(wndClass.lpszClassName, GetModuleHandle(NULL));
}

bool WindowManager::WindowIsRunning()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{

		//	Receive a quit message
		if (msg.message == WM_QUIT)
			return false;
		//	Translate the message 
		TranslateMessage(&msg);
		//	Send message to your window procedure
		DispatchMessage(&msg);
	}


	return true;
}