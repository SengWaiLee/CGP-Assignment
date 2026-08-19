#include "DirectInputManager.h"
#include <iostream>
using namespace std;
BYTE DirectInputManager::diKeys[256];
DIMOUSESTATE DirectInputManager::mouseState;
DirectInputManager::DirectInputManager()
{
	//	Create the Direct Input object.
	HRESULT hr = DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (void**)&dInput, NULL);

	//	Create the keyboard device.
	hr = dInput->CreateDevice(GUID_SysKeyboard, &dInputKeyboardDevice, NULL);
	if (FAILED(hr))
		cout << "Failed to create direct input keyboard device" << endl;
	//Create mouse device
	hr = dInput->CreateDevice(GUID_SysMouse, &dInputMouseDevice, NULL);
	if (FAILED(hr))
		cout << "Failed to create direct input mouse device" << endl;

	//	Set the input data format.
	hr = dInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
		cout << "Failed to set keyboard data format " << endl;
	hr = dInputMouseDevice->SetDataFormat(&c_dfDIMouse);
	if (FAILED(hr))
		cout << "Failed to set mouse data format " << endl;

	//	Set the cooperative level.
	hr = dInputKeyboardDevice->SetCooperativeLevel(WindowManager::g_hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if (FAILED(hr))
		cout << "Failed to keyboard's SetCooperative Level  " << endl;
	hr = dInputMouseDevice->SetCooperativeLevel(WindowManager::g_hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if (FAILED(hr))
		cout << "Failed to mouse's SetCooperative Level  " << endl;

	hr = dInputKeyboardDevice->Acquire();
	if (FAILED(hr))
		cout << "Failed to acquire keyboard  " << endl;
	hr = dInputMouseDevice->Acquire();
	if (FAILED(hr))
		cout << "Failed to acquire mouse  " << endl;
}

void DirectInputManager::GettingInput()
{	//	Get immediate Keyboard Data.
	dInputKeyboardDevice->GetDeviceState(256, diKeys);
	dInputMouseDevice->GetDeviceState(sizeof(mouseState), (LPVOID)&mouseState);
	//Acquire Device

}


void DirectInputManager::CleanUpDirectInput()
{
	dInputKeyboardDevice->Unacquire();
	dInputKeyboardDevice->Release();
	dInputKeyboardDevice = NULL;
	dInputMouseDevice->Unacquire();
	dInputMouseDevice->Release();
	dInputMouseDevice = NULL;

	//	Release DirectInput.
	dInput->Release();
	dInput = NULL;
}

DirectInputManager::~DirectInputManager()
{}