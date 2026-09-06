#include "Level1.h"
#include <iostream>

void Level1::InitialiseGame()
{
	AudioManager::PlayLevel1Sound();
	
	friction = 0.9f;
	gravity = 9.8f;

	bg = new GameObject((LPSTR)"Assets/level1bg.png", 1, 1, 1920, 1080, 0, 1, 1, 0, 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
	gameObject.push_back(bg);

	platform5 = new GameObject((LPSTR)"Assets/platform.png", 1, 1, 2048, 925, 0, 1, 1, 0, 0, D3DXVECTOR2(1500.0f, 525.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.03f, 0.01f));
	gameObject.push_back(platform5);

	platform4 = new GameObject((LPSTR)"Assets/platform.png", 1, 1, 2048, 925, 0, 1, 1, 0, 0, D3DXVECTOR2(950.0f, 350.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.2f, 0.01f));
	gameObject.push_back(platform4);

	platform3 = new GameObject((LPSTR)"Assets/platform.png", 1, 1, 2048, 925, 0, 1, 1, 0, 0, D3DXVECTOR2(1250.0f, 625.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.025f, 0.01f));
	gameObject.push_back(platform3);

	platform2 = new GameObject((LPSTR)"Assets/platform.png", 1, 1, 2048, 925, 0, 1, 1, 0, 0, D3DXVECTOR2(800.0f, 725.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.1f, 0.01f));
	gameObject.push_back(platform2);

	platform = new GameObject((LPSTR)"Assets/platform.png", 1, 1, 2048, 925, 0, 1, 1, 0, 0, D3DXVECTOR2(500.0f, 850.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.07f, 0.01f));
	gameObject.push_back(platform);

	destination = new GameObject((LPSTR)"Assets/flag.png", 1, 5, 300, 60, 0, 5, 0, 0, 0, D3DXVECTOR2(950.0f, 290.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
	gameObject.push_back(destination);

	militia = new GameObject((LPSTR)"Assets/militia.png", 4, 4, 128, 192, 2, 4, 0, 25, 10, D3DXVECTOR2(0.0f, 100.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 700, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(2.0f, 2.0f));
	gameObject.push_back(militia);
}

void Level1::Update()
{
	for (int i = 0; i < frameTimer->framesToUpdate(); i++)
	{
		destination->currentFrame++;

		// Update militia animation rectangle
		militia->animRect.top = militia->direction * militia->spriteHeight;
		militia->animRect.bottom = militia->animRect.top + militia->spriteHeight;
		militia->animRect.left = militia->currentFrame % militia->maxFrame % militia->col * militia->spriteWidth;
		militia->animRect.right = militia->animRect.left + militia->spriteWidth;

		// Update destination animation rectangle
		destination->animRect.top = destination->direction * destination->spriteHeight;
		destination->animRect.bottom = destination->animRect.top + destination->spriteHeight;
		destination->animRect.left = destination->currentFrame % destination->maxFrame % destination->col * destination->spriteWidth;
		destination->animRect.right = destination->animRect.left + destination->spriteWidth;

		// Add frictional and gravitational force to militia
		militia->vel.x *= friction;
		militia->vel.y += gravity;

		// Reset walking state
		isWalking = false;

		float playerCenterX = militia->pos.x + militia->spriteWidth * militia->scaling.x / 2.0f;

		float pan =(playerCenterX /	WindowManager::ScreenWidth) * 2.0f - 1.0f;

		if (pan < -1.0f)
		{
			pan = -1.0f;
		}

		if (pan > 1.0f)
		{
			pan = 1.0f;
		}

		// Checking input for space bar (Jump)
		if (DirectInputManager::diKeys[DIK_SPACE] & 0x80) 
		{
			if (canJump == true) 
			{
				AudioManager::PlayJumpSound(pan);

				militia->jumpAccel.y = militia->jumpForce / militia->mass;

				militia->vel -= militia->jumpAccel;

				canJump = false;
				playLandSound = true;
			}
		}

		// Checking input for D key (Move right)
		if (DirectInputManager::diKeys[DIK_D] & 0x80) 
		{
			militia->direction = 2;
			militia->currentFrame++;

			militia->accel.x = militia->speed / militia->mass;

			militia->vel += militia->accel;

			// Check walking
			if (canJump) 
			{
				isWalking = true;
			}
		}

		// Check input for A key (Move left)
		if (DirectInputManager::diKeys[DIK_A] & 0x80) {
			militia->direction = 1;
			militia->currentFrame++;

			militia->accel.x = militia->speed / militia->mass;
			militia->vel -= militia->accel;

			// Check walking
			if (canJump) 
			{
				isWalking = true;
			}
		}

		// Footstep trigger per frame
		int currentAnimationFrame = militia->currentFrame % militia->maxFrame;

		if (isWalking && currentAnimationFrame != previousFrame) 
		{
			if (currentAnimationFrame == 1 || currentAnimationFrame == 3) 
			{
				cout << "FOOTSTEP TRIGGERED - Frame: " << currentAnimationFrame << endl;
				AudioManager::PlayFootstepSound(pan);
			}
		}

		previousFrame = currentAnimationFrame;

		// Update collision rectangle before updating position
		float previousBottom = militia->colRect.bottom;

		// Update position
		militia->pos += militia->vel;

		// Update collision rectangle after updating position
		militia->colRect.top = militia->pos.y;
		militia->colRect.bottom = militia->colRect.top + (float)militia->spriteHeight * militia->scaling.y;
		militia->colRect.left = militia->pos.x;
		militia->colRect.right = militia->colRect.left + (float)militia->spriteWidth * militia->scaling.x;

		// Collision detection between player and the platform
		if (militia->vel.y >= 0 && previousBottom <= platform->colRect.top && militia->colRect.bottom >= platform->colRect.top && militia->colRect.right > platform->colRect.left && militia->colRect.left < platform->colRect.right)
		{
			if (playLandSound)
			{
				AudioManager::PlayLandSound(pan);
				playLandSound = false;
			}

			// Put Militia exactly on top of platform
			militia->pos.y = platform->colRect.top - (militia->spriteHeight * militia->scaling.y);

			militia->vel.y = 0;
			canJump = true;

			// Update vertical collision rectangle
			militia->colRect.top = militia->pos.y;

			militia->colRect.bottom = militia->colRect.top + (float)militia->spriteHeight * militia->scaling.y;
		}

		// Collision detection between player and the platform2
		if (militia->vel.y >= 0 && previousBottom <= platform2->colRect.top && militia->colRect.bottom >= platform2->colRect.top && militia->colRect.right > platform2->colRect.left && militia->colRect.left < platform2->colRect.right)
		{
			if (playLandSound)
			{
				AudioManager::PlayLandSound(pan);
				playLandSound = false;
			}

			militia->pos.y = platform2->colRect.top - (militia->spriteHeight * militia->scaling.y);

			militia->vel.y = 0;
			canJump = true;

			militia->colRect.top = militia->pos.y;

			militia->colRect.bottom = militia->colRect.top + (float)militia->spriteHeight * militia->scaling.y;
		}

		// Collision detection between player and the platform3
		if (militia->vel.y >= 0 && previousBottom <= platform3->colRect.top && militia->colRect.bottom >= platform3->colRect.top && militia->colRect.right > platform3->colRect.left && militia->colRect.left < platform3->colRect.right)
		{
			if (playLandSound)
			{
				AudioManager::PlayLandSound(pan);
				playLandSound = false;
			}

			militia->pos.y = platform3->colRect.top - (militia->spriteHeight * militia->scaling.y);

			militia->vel.y = 0;
			canJump = true;

			militia->colRect.top = militia->pos.y;

			militia->colRect.bottom = militia->colRect.top + (float)militia->spriteHeight * militia->scaling.y;
		}

		// Collision detection between player and the platform4
		if (militia->vel.y >= 0 && previousBottom <= platform4->colRect.top && militia->colRect.bottom >= platform4->colRect.top && militia->colRect.right > platform4->colRect.left && militia->colRect.left < platform4->colRect.right)
		{
			if (playLandSound)
			{
				AudioManager::PlayLandSound(pan);
				playLandSound = false;
			}

			militia->pos.y = platform4->colRect.top - (militia->spriteHeight * militia->scaling.y);

			militia->vel.y = 0;
			canJump = true;

			militia->colRect.top = militia->pos.y;

			militia->colRect.bottom = militia->colRect.top + (float)militia->spriteHeight * militia->scaling.y;
		}

		// Collision detection between player and the platform5
		if (militia->vel.y >= 0 && previousBottom <= platform5->colRect.top && militia->colRect.bottom >= platform5->colRect.top && militia->colRect.right > platform5->colRect.left && militia->colRect.left < platform5->colRect.right)
		{
			if (playLandSound)
			{
				AudioManager::PlayLandSound(pan);
				playLandSound = false;
			}

			militia->pos.y = platform5->colRect.top - (militia->spriteHeight * militia->scaling.y);

			militia->vel.y = 0;
			canJump = true;

			militia->colRect.top = militia->pos.y;

			militia->colRect.bottom = militia->colRect.top + (float)militia->spriteHeight * militia->scaling.y;
		}

		// Militia boundary 
		float militiaWidth = militia->spriteWidth * militia->scaling.x;
		float militiaHeight = militia->spriteHeight * militia->scaling.y;

		// Bottom boundary / ground
		if (militia->pos.y > groundY - militiaHeight)
		{
			militia->pos.y = groundY - militiaHeight;

			if (playLandSound)
			{
				AudioManager::PlayLandSound(pan);
				playLandSound = false;
			}

			canJump = true;
			militia->vel.y = 0;
		}

		// Top boundary
		if (militia->pos.y < 0)
		{
			militia->pos.y = 0;
		}

		// Right boundary
		if (militia->pos.x > WindowManager::ScreenWidth - militiaWidth)
		{
			militia->pos.x = WindowManager::ScreenWidth - militiaWidth;
		}

		// Left boundary
		if (militia->pos.x < 0)
		{
			militia->pos.x = 0;
		}

		// Update collision rectangle
		militia->colRect.top = militia->pos.y;
		militia->colRect.bottom = militia->colRect.top + (float)militia->spriteHeight * militia->scaling.y;
		militia->colRect.left = militia->pos.x;
		militia->colRect.right = militia->colRect.left + (float)militia->spriteWidth * militia->scaling.x;

		// Collision detection between player and the flag
		if (CollisionDetection(militia->colRect, destination->colRect))
		{
			cout << "won" << endl;

			AudioManager::StopBackgroundMusic();

			Game* currentGame = Game::gameStack.back();

			currentGame->CleanUp();

			Game::gameStack.pop_back();

			delete currentGame;
			currentGame = nullptr;

			Game::gameStack.push_back(new GameOver());

			Game::gameStack.back()->InitialiseGame();

			return;
		}

		if (DirectInputManager::diKeys[DIK_B] & 0x80) {
			Game* currentGame = Game::gameStack.back();

			currentGame->CleanUp();
			Game::gameStack.pop_back();

			delete currentGame;
			currentGame = nullptr;

			AudioManager::PlayMainMenuSound();

			return;
		}
	}
}

void Level1::RenderText()
{
	RECT levelRect;

	levelRect.left = 0;
	levelRect.top = 50;
	levelRect.right = WindowManager::ScreenWidth;
	levelRect.bottom = 120;

	DirectXManager::font->DrawText(NULL, "LEVEL 1", -1, &levelRect, DT_CENTER, D3DCOLOR_XRGB(255, 255, 255));

	RECT objectiveRect;

	objectiveRect.left = 50;
	objectiveRect.top = 50;
	objectiveRect.right = 1000;
	objectiveRect.bottom = 120;

	DirectXManager::font->DrawText(NULL, "Objective: Reach the flag", -1, &objectiveRect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));

	RECT movementRect;

	movementRect.left = 50;
	movementRect.top = 120;
	movementRect.right = 600;
	movementRect.bottom = 180;

	DirectXManager::font->DrawText(NULL, "A / D: Movement", -1, &movementRect, DT_LEFT,D3DCOLOR_XRGB(255, 255, 255));

	RECT jumpRect;

	jumpRect.left = 50;
	jumpRect.top = 180;
	jumpRect.right = 600;
	jumpRect.bottom = 240;

	DirectXManager::font->DrawText(NULL, "SPACE: Jump", -1, &jumpRect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));

	RECT InstrucRect;

	InstrucRect.left = 50;
	InstrucRect.top = 240;
	InstrucRect.right = 600;
	InstrucRect.bottom = 300;

	DirectXManager::font->DrawText(NULL, "B: Main Menu", -1, &InstrucRect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
}

void Level1::CleanUp()
{
	for (GameObject* obj : gameObject)
	{
		if (obj != nullptr)
		{
			if (obj->texture != nullptr)
			{
				obj->texture->Release();
				obj->texture = nullptr;
			}

			delete obj;
		}
	}

	gameObject.clear();

	bg = nullptr;
	platform5 = nullptr;
	platform4 = nullptr;
	platform3 = nullptr;
	platform2 = nullptr;
	platform = nullptr;
	destination = nullptr;
	militia = nullptr;
}

Level1::Level1()
{}