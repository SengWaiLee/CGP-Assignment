#include "GameOver.h"

void GameOver::InitialiseGame()
{
	// Initialize texture(background,game over), button(exit, retry), mouse cursor
	AudioManager::StopBackgroundMusic();
	AudioManager::PlayVictorySound();
	
	RECT MainBGRect;
	MainBGRect.left = 40;
	MainBGRect.top = 460;
	MainBGRect.right = 1960;
	MainBGRect.bottom = 1540;

	RECT AsteroidBG1Rect;
	AsteroidBG1Rect.left = 0;
	AsteroidBG1Rect.top = 0;
	AsteroidBG1Rect.right = 665;
	AsteroidBG1Rect.bottom = 738;

	RECT AsteroidBG2Rect;
	AsteroidBG2Rect.left = 0;
	AsteroidBG2Rect.top = 0;
	AsteroidBG2Rect.right = 738;
	AsteroidBG2Rect.bottom = 665;

	NebulaBG.Initialise("Assets/NebulaBG.png",MainBGRect,0.10f);
	FarStarsBG.Initialise("Assets/FarStarsBG.png",MainBGRect,0.20f);
	MiddleStarsBG.Initialise("Assets/MiddleStarsBG.png",MainBGRect,0.35f);
	PlanetBG.Initialise("Assets/PlanetBG.png",MainBGRect,0.45f);
	DenseStarsBG.Initialise("Assets/DenseStarsBG.png",MainBGRect,0.60f);
	NearStarsBG.Initialise("Assets/NearStarsBG.png",MainBGRect,0.80f);
	AsteroidBG1.Initialise("Assets/AsteroidBG1.png",AsteroidBG1Rect,1.00f,150.0f);
	AsteroidBG2.Initialise("Assets/AsteroidBG2.png",AsteroidBG2Rect,1.20f,300.0f);

	gameOver = new GameObject((LPSTR)"Assets/victory.png", 1, 1, 512, 256, 0, 1, 1, 0, 0, D3DXVECTOR2(448.0f, 100.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(2.0f, 2.0f));
	gameObject.push_back(gameOver);
	replayButton = new GameObject((LPSTR)"Assets/replaybutton.png", 1, 1, 256, 65, 0, 1, 1, 0, 0, D3DXVECTOR2(832.0f, 600.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.5f, 1.5f));
	gameObject.push_back(replayButton);
	mainMenuButton = new GameObject((LPSTR)"Assets/mainmenubutton.png", 1, 1, 256, 65, 0, 1, 1, 0, 0, D3DXVECTOR2(832.0f, 770.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.5f, 1.5f));
	gameObject.push_back(mainMenuButton);
	mouseCursor = new GameObject((LPSTR)"Assets/pointer.png", 1, 1, 32, 32, 0, 1, 1, 0, 0, D3DXVECTOR2(700.0f, 500.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
	gameObject.push_back(mouseCursor);
}

void GameOver::Update()
{
	replayButton = gameObject.at(1);
	mainMenuButton = gameObject.at(2);
	mouseCursor = gameObject.at(3);
	
	for (int i = 0; i < frameTimer->framesToUpdate(); i++)
	{
		NebulaBG.Update();
		FarStarsBG.Update();
		MiddleStarsBG.Update();
		PlanetBG.Update();
		DenseStarsBG.Update();
		NearStarsBG.Update();

		AsteroidBG1.Update();
		AsteroidBG2.Update();

		// Update mouse cursor position
		mouseCursor->pos.x += DirectInputManager::mouseState.lX * 5.0;
		mouseCursor->pos.y += DirectInputManager::mouseState.lY * 5.0;

		// Mouse Boundary
		// Up
		if (mouseCursor->pos.y < 0)
		{
			mouseCursor->pos.y = 0;
		}

		// Down
		if (mouseCursor->pos.y > WindowManager::ScreenHeight - mouseCursor->spriteHeight * mouseCursor->scaling.y)
		{
			mouseCursor->pos.y = WindowManager::ScreenHeight - mouseCursor->spriteHeight * mouseCursor->scaling.y;
		}

		// Right
		if (mouseCursor->pos.x > WindowManager::ScreenWidth - mouseCursor->spriteWidth * mouseCursor->scaling.x)
		{
			mouseCursor->pos.x = WindowManager::ScreenWidth - mouseCursor->spriteWidth * mouseCursor->scaling.x;
		}

		// Left
		if (mouseCursor->pos.x < 0)
		{
			mouseCursor->pos.x = 0;
		}

		// Update collision rectangle after boundary correction
		mouseCursor->colRect.top = mouseCursor->pos.y;
		mouseCursor->colRect.bottom = mouseCursor->colRect.top + ((float)mouseCursor->spriteHeight * mouseCursor->scaling.y);
		mouseCursor->colRect.left = mouseCursor->pos.x;
		mouseCursor->colRect.right = mouseCursor->colRect.left + ((float)mouseCursor->spriteWidth * mouseCursor->scaling.x);

		GameObject* currentHoveredButton = nullptr;

		if (CollisionDetection(replayButton->colRect, mouseCursor->colRect))
		{
			currentHoveredButton = replayButton;
		}
		else if (CollisionDetection(mainMenuButton->colRect, mouseCursor->colRect))
		{
			currentHoveredButton = mainMenuButton;
		}

		if (currentHoveredButton != nullptr && currentHoveredButton != previousHoveredButton)
		{
			AudioManager::PlayMouseHoverSound();
		}

		previousHoveredButton = currentHoveredButton;

		// Collision detection of mouse cursor with the replay
		if (CollisionDetection(replayButton->colRect, mouseCursor->colRect))
		{
			replayButton->scaling.x = 1.55f;
			replayButton->scaling.y = 1.55f;


			if (DirectInputManager::mouseState.rgbButtons[0] & 0x80) {
				AudioManager::StopVictorySound();
				AudioManager::PlaySelectSound();

				Game* currentGame = Game::gameStack.back();

				currentGame->CleanUp();
				Game::gameStack.pop_back();

				delete currentGame;
				currentGame = nullptr;

				Game::gameStack.push_back(new Level1());
				Game::gameStack.back()->InitialiseGame();

				return;
			}
		}
		else
		{
			replayButton->scaling.x = 1.50f;
			replayButton->scaling.y = 1.50f;
		}

		// Collision detection of mouse cursor with the mainMenu button
		if (CollisionDetection(mouseCursor->colRect, mainMenuButton->colRect))
		{
			mainMenuButton->scaling.x = 1.55f;
			mainMenuButton->scaling.y = 1.55f;

			if (DirectInputManager::mouseState.rgbButtons[0] & 0x80)
			{
				AudioManager::StopVictorySound();
				AudioManager::PlaySelectSound(); 
				
				Game* currentGame = Game::gameStack.back();

				currentGame->CleanUp();
				Game::gameStack.pop_back();

				delete currentGame;
				currentGame = nullptr;

				AudioManager::PlayMainMenuSound();

				return;
			}
		}
		else
		{
			mainMenuButton->scaling.x = 1.50f;
			mainMenuButton->scaling.y = 1.50f;
		}
	}
}

void GameOver::Render()
{
	DirectXManager::myVirtualGPU->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	DirectXManager::myVirtualGPU->BeginScene();

	DirectXManager::spriteBrush->Begin(D3DXSPRITE_ALPHABLEND);

	NebulaBG.Render();
	FarStarsBG.Render();
	MiddleStarsBG.Render();
	PlanetBG.Render();
	DenseStarsBG.Render();
	NearStarsBG.Render();

	AsteroidBG1.Render();
	AsteroidBG2.Render();

	for (GameObject* object : gameObject)
	{
		D3DXVECTOR2* scalingCenter = NULL;

		if (object == replayButton || object == mainMenuButton)
		{
			scalingCenter = &object->spriteCenter;
		}

		D3DXMatrixTransformation2D(&object->mat, scalingCenter, 0.0f, &object->scaling, &object->spriteCenter, object->rotation, &object->pos);

		DirectXManager::spriteBrush->SetTransform(&object->mat);

		DirectXManager::spriteBrush->Draw(object->texture, &object->animRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	}

	DirectXManager::spriteBrush->End();

	DirectXManager::myVirtualGPU->EndScene();

	DirectXManager::myVirtualGPU->Present(NULL, NULL, NULL, NULL);
}

void GameOver::CleanUp()
{
	NebulaBG.CleanUp();
	FarStarsBG.CleanUp();
	MiddleStarsBG.CleanUp();
	PlanetBG.CleanUp();
	DenseStarsBG.CleanUp();
	NearStarsBG.CleanUp();

	AsteroidBG1.CleanUp();
	AsteroidBG2.CleanUp();

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

	gameOver = nullptr;
	replayButton = nullptr;
	mainMenuButton = nullptr;
	mouseCursor = nullptr;
}

GameOver::GameOver()
{}