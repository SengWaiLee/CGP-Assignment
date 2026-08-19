#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "WindowManager.h"
#ifndef DIRECTXMANAGER_H
#define DIRECTXMANAGER_H
class DirectXManager
{
public:
	static IDirect3DDevice9* myVirtualGPU;
	IDirect3D9* direct3D9 = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dPP;
	static LPD3DXSPRITE spriteBrush;
	static LPD3DXFONT font;
	static LPD3DXLINE line;

	DirectXManager();
	~DirectXManager();
	void CleanUpDirectX();

};
#endif