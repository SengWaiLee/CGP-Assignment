#include "DirectXManager.h"
#include <iostream>
using namespace std;
IDirect3DDevice9* DirectXManager::myVirtualGPU;
LPD3DXSPRITE  DirectXManager::spriteBrush = NULL;
LPD3DXFONT  DirectXManager::font = NULL;
LPD3DXLINE  DirectXManager::line = NULL;
DirectXManager::DirectXManager()
{

	ZeroMemory(&d3dPP, sizeof(d3dPP));

	d3dPP.Windowed = false;
	d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dPP.BackBufferCount = 1;
	d3dPP.BackBufferWidth = WindowManager::ScreenWidth;
	d3dPP.BackBufferHeight = WindowManager::ScreenHeight;
	d3dPP.hDeviceWindow = WindowManager::g_hWnd;

	HRESULT hr = direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, WindowManager::g_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPP, &myVirtualGPU);

	if (FAILED(hr))
		printf("failed to create virtual gpu");

	//	Create font. Study the documentation.
	hr = D3DXCreateFont(myVirtualGPU, 25, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &font);
	//	Create sprite. Study the documentation. 
	hr = D3DXCreateSprite(myVirtualGPU, &spriteBrush);
	if (FAILED(hr))
		cout << "Failed to create sprite brush" << endl;
	hr = D3DXCreateLine(myVirtualGPU, &line);
	if (FAILED(hr))
		cout << "Failed to create line brush" << endl;
}

DirectXManager::~DirectXManager()
{}

void DirectXManager::CleanUpDirectX()
{
	spriteBrush->Release();
	spriteBrush = NULL;
	//	Release the device when exiting.
	myVirtualGPU->Release();
	//	Reset pointer to NULL, a good practice.
	myVirtualGPU = NULL;
}