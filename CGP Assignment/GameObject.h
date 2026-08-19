#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include "DirectXManager.h"
class GameObject
{
public:
	int row;
	int col;
	int textureWidth;
	int textureHeight;
	int spriteWidth;
	int spriteHeight;
	int maxFrame;
	int currentFrame;
	int direction;
	int speed;
	int mass;
	D3DXVECTOR2 pos;
	D3DXVECTOR2 vel;
	D3DXVECTOR2 accel;
	int jumpForce;
	D3DXVECTOR2 jumpVel;
	D3DXVECTOR2 jumpAccel;
	D3DXMATRIX mat;
	D3DXVECTOR2 scaling;
	D3DXVECTOR2 spriteCenter;
	D3DXVECTOR2 engineForce;
	float rotation;
	RECT animRect;
	RECT colRect;
	LPDIRECT3DTEXTURE9 texture;
	GameObject(LPSTR textureName, int row, int col, int textureWidth, int textureHeight, int direction, int maxFrame, int currentFrame, int speed, int mass, D3DXVECTOR2 pos, D3DXVECTOR2 vel, D3DXVECTOR2 accel, int jumpForce,
		D3DXVECTOR2 jumpVel, D3DXVECTOR2 jumpAccel, D3DXVECTOR2 scaling);
	GameObject();
}
;