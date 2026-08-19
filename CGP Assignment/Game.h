#pragma once
#include <dinput.h>
#include "DirectXManager.h"
#include "GameObject.h"
#include <vector>
#include "FrameTimer.h"
#ifndef GAME_H
#define GAME_H
using namespace std;
class Game
{
public:
	static vector<Game*> gameStack;
	virtual void InitialiseGame();
	virtual void Update();
	void Render();
	virtual void CleanUp();
	Game();
	bool CollisionDetection(RECT A, RECT B);
	bool circleCollisionDetection(float a, float b, D3DXVECTOR2 positionA, D3DXVECTOR2 positionB);
	FrameTimer* frameTimer = new FrameTimer();
	vector<GameObject*> gameObject;
};
#endif