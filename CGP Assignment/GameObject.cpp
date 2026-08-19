#include "GameObject.h"
using namespace std;

GameObject::GameObject(LPSTR textureName, int row, int col, int textureWidth, int textureHeight, int direction, int maxFrame, int currentFrame, int speed, int mass, D3DXVECTOR2 pos, D3DXVECTOR2 vel, D3DXVECTOR2 accel, int jumpForce,
	D3DXVECTOR2 jumpVel, D3DXVECTOR2 jumpAccel, D3DXVECTOR2 scaling)
{
	HRESULT hr = D3DXCreateTextureFromFile(DirectXManager::myVirtualGPU, textureName, &this->texture);
	if (FAILED(hr))
		cout << "Failed to create texture" << endl;
	this->row = row;
	this->col = col;
	this->textureWidth = textureWidth;
	this->textureHeight = textureHeight;
	this->spriteHeight = textureHeight / row;
	this->spriteWidth = textureWidth / col;
	this->maxFrame = maxFrame;
	this->speed = speed;
	this->mass = mass;
	this->pos = pos;
	this->vel = vel;
	this->accel = accel;
	this->jumpForce = jumpForce;
	this->jumpVel = jumpVel;
	this->jumpAccel = jumpAccel;
	this->direction = direction;
	this->animRect.top = direction * this->spriteHeight;
	this->animRect.bottom = this->animRect.top + this->spriteHeight;
	this->animRect.left = currentFrame % maxFrame % col * this->spriteWidth;
	this->animRect.right = this->animRect.left + this->spriteWidth;
	this->colRect.top = this->pos.y;
	this->colRect.bottom = this->colRect.top + ((float)this->spriteHeight * scaling.y);
	this->colRect.left = this->pos.x;
	this->colRect.right = this->colRect.left + ((float)this->spriteWidth * scaling.x);
	this->scaling = scaling;
	this->spriteCenter = D3DXVECTOR2((float)spriteWidth / 2, (float)spriteHeight / 2);
}

GameObject::GameObject()
{}