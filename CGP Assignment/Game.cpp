#include "Game.h"
#include <iostream>
using namespace std;

vector<Game*> Game::gameStack;

void Game::InitialiseGame()
{}

void Game::Update()
{}

void Game::Render()
{

	DirectXManager::myVirtualGPU->BeginScene();
	DirectXManager::myVirtualGPU->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
	DirectXManager::spriteBrush->Begin(D3DXSPRITE_ALPHABLEND);
	for (GameObject* gameObject : gameObject) {
		D3DXMatrixTransformation2D(&gameObject->mat, NULL, 0.0, &gameObject->scaling, &gameObject->spriteCenter, gameObject->rotation, &gameObject->pos);
		DirectXManager::spriteBrush->SetTransform(&gameObject->mat);
		HRESULT hr = DirectXManager::spriteBrush->Draw(gameObject->texture, &gameObject->animRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
		if (FAILED(hr))
			cout << "failure to create texture" << endl;
	}

	DirectXManager::spriteBrush->End();
	DirectXManager::myVirtualGPU->EndScene();
	DirectXManager::myVirtualGPU->Present(NULL, NULL, NULL, NULL);
}

void Game::CleanUp()
{
	for (GameObject* gameObject : gameObject) {
		gameObject->texture->Release();
		gameObject->texture = NULL;
	}
	gameObject.clear();
}

Game::Game()
{

	frameTimer->init(30);
}

bool Game::CollisionDetection(RECT A, RECT B) {
	//collision for rect

	//check all the false contition
	//when A top is under B bottom 
	//when A bottom is upside B top
	//when A left is at left of B right
	//when A right is at right of B left
	if (A.top > B.bottom) {
		return false;
	}
	if (A.bottom < B.top) {
		return false;
	}
	if (A.left > B.right) {
		return false;
	}
	if (A.right < B.left) {
		return false;
	}
	else {
		return true;
	}
}

bool Game::circleCollisionDetection(float a, float b, D3DXVECTOR2 positionA, D3DXVECTOR2 positionB)
{
	D3DXVECTOR2 distance = positionA - positionB;
	if (pow(a + b, 2) > D3DXVec2LengthSq(&distance)) {
		return true;
	}
	return false;
}