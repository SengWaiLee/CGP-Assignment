#include "MainMenu.h"
#include <iostream>

using namespace std;

void MainMenu::InitialiseGame()
{
	AudioManager::PlayMainMenuSound();

	//Initialize texture(background, game title), button(startgame, exitgame), mouse cursor
	if (AudioManager::isMuted)
	{
		volume = 0;
	}
	else
	{
		volume = (int)(AudioManager::SOUND_VOLUME * 100);
	}

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

	NebulaBG.Initialise("Assets/NebulaBG.png", MainBGRect, 0.10f);
	FarStarsBG.Initialise("Assets/FarStarsBG.png", MainBGRect, 0.20f);
	MiddleStarsBG.Initialise("Assets/MiddleStarsBG.png",MainBGRect, 0.35f);
	PlanetBG.Initialise("Assets/PlanetBG.png", MainBGRect, 0.45f);
	DenseStarsBG.Initialise("Assets/DenseStarsBG.png", MainBGRect, 0.60f);
	NearStarsBG.Initialise("Assets/NearStarsBG.png", MainBGRect, 0.80f);

	AsteroidBG1.Initialise("Assets/AsteroidBG1.png", AsteroidBG1Rect, 1.00f, 150.0f);
	AsteroidBG2.Initialise("Assets/AsteroidBG2.png", AsteroidBG2Rect, 1.20f, 300.0f);

	gameTitle = new GameObject((LPSTR)"Assets/gametitle.png", 1, 1, 252, 320, 0, 1, 1, 0, 0, D3DXVECTOR2(680.0f, 40.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(2.2f, 1.7f));
	gameObject.push_back(gameTitle);
	level1Button = new GameObject((LPSTR)"Assets/level1button.png", 1, 1, 256, 65, 0, 1, 1, 0, 0, D3DXVECTOR2(832.0f, 510.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.5f, 1.5f));
	gameObject.push_back(level1Button);
	level2Button = new GameObject((LPSTR)"Assets/level2button.png", 1, 1, 256, 65, 0, 1, 1, 0, 0, D3DXVECTOR2(832.0f, 670.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.5f, 1.5f));
	gameObject.push_back(level2Button);
	quitGameButton = new GameObject((LPSTR)"Assets/quitbutton.png", 1, 1, 256, 65, 0, 1, 1, 0, 0, D3DXVECTOR2(832.0f, 830.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.5f, 1.5f));
	gameObject.push_back(quitGameButton);
	muteButton = new GameObject((LPSTR)"Assets/mutebutton.png", 1, 1, 64, 64, 0, 1, 1, 0, 0, D3DXVECTOR2(635.0f, 970.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
	gameObject.push_back(muteButton);
	minusButton = new GameObject((LPSTR)"Assets/minusbutton.png", 1, 1, 64, 64, 0, 1, 1, 0, 0, D3DXVECTOR2(745.0f, 970.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
	gameObject.push_back(minusButton);
	addButton = new GameObject((LPSTR)"Assets/addbutton.png", 1, 1, 64, 64, 0, 1, 1, 0, 0, D3DXVECTOR2(1115.0f, 970.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
	gameObject.push_back(addButton);
	unmuteButton = new GameObject((LPSTR)"Assets/unmutebutton.png", 1, 1, 64, 64, 0, 1, 1, 0, 0, D3DXVECTOR2(1225.0f, 970.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
	gameObject.push_back(unmuteButton);
	mouseCursor = new GameObject((LPSTR)"Assets/pointer.png", 1, 1, 32, 32, 0, 1, 1, 0, 0, D3DXVECTOR2(700.0f, 500.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
	gameObject.push_back(mouseCursor);
}

void MainMenu::Update()
{
	bool leftMouseDown = DirectInputManager::mouseState.rgbButtons[0] & 0x80;

	if (!leftMouseDown)
	{
		levelButtonReady = true;
	}

	for (int i = 0; i < frameTimer->framesToUpdate(); i++)
	{
		//update parallax background
		NebulaBG.Update();
		FarStarsBG.Update();
		MiddleStarsBG.Update();
		PlanetBG.Update();
		DenseStarsBG.Update();
		NearStarsBG.Update();
		AsteroidBG1.Update();
		AsteroidBG2.Update();

		//update mouse cursor position
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

		if (CollisionDetection(level1Button->colRect, mouseCursor->colRect))
		{
			currentHoveredButton = level1Button;
		}
		else if (CollisionDetection(level2Button->colRect, mouseCursor->colRect))
		{
			currentHoveredButton = level2Button;
		}
		else if (CollisionDetection(quitGameButton->colRect, mouseCursor->colRect))
		{
			currentHoveredButton = quitGameButton;
		}
		else if (circleCollisionDetection(
			mouseCursor->spriteWidth * mouseCursor->scaling.x / 2,
			muteButton->spriteWidth * muteButton->scaling.x / 2 * 0.7,
			mouseCursor->pos + mouseCursor->spriteCenter,
			muteButton->pos + muteButton->spriteCenter))
		{
			currentHoveredButton = muteButton;
		}
		else if (circleCollisionDetection(
			mouseCursor->spriteWidth * mouseCursor->scaling.x / 2,
			minusButton->spriteWidth * minusButton->scaling.x / 2 * 0.7,
			mouseCursor->pos + mouseCursor->spriteCenter,
			minusButton->pos + minusButton->spriteCenter))
		{
			currentHoveredButton = minusButton;
		}
		else if (circleCollisionDetection(
			mouseCursor->spriteWidth * mouseCursor->scaling.x / 2,
			addButton->spriteWidth * addButton->scaling.x / 2 * 0.7,
			mouseCursor->pos + mouseCursor->spriteCenter,
			addButton->pos + addButton->spriteCenter))
		{
			currentHoveredButton = addButton;
		}
		else if (circleCollisionDetection(
			mouseCursor->spriteWidth * mouseCursor->scaling.x / 2,
			unmuteButton->spriteWidth * unmuteButton->scaling.x / 2 * 0.7,
			mouseCursor->pos + mouseCursor->spriteCenter,
			unmuteButton->pos + unmuteButton->spriteCenter))
		{
			currentHoveredButton = unmuteButton;
		}

		if (currentHoveredButton != nullptr && currentHoveredButton != previousHoveredButton)
		{
			AudioManager::PlayMouseHoverSound();
		}

		previousHoveredButton = currentHoveredButton;

		// collision detection of mouse cursor with the level 1 button
		if (CollisionDetection(level1Button->colRect, mouseCursor->colRect))
		{
			level1Button->scaling.x = 1.55f;
			level1Button->scaling.y = 1.55f;

			if (levelButtonReady && leftMouseDown)
			{
				levelButtonReady = false;

				AudioManager::StopBackgroundMusic();
				AudioManager::PlaySelectSound();

				Game::gameStack.push_back(new Level1());
				Game::gameStack.back()->InitialiseGame();

				return;
			}
		}
		else {
			level1Button->scaling.x = 1.50f;
			level1Button->scaling.y = 1.50f;
		}

		// collision detection of mouse cursor with the level2Button
		if (CollisionDetection(level2Button->colRect, mouseCursor->colRect))
		{
			level2Button->scaling.x = 1.55f;
			level2Button->scaling.y = 1.55f;

			if (levelButtonReady && leftMouseDown)
			{
				levelButtonReady = false;

				AudioManager::StopBackgroundMusic();
				AudioManager::PlaySelectSound();

				Game::gameStack.push_back(new Level2());
				Game::gameStack.back()->InitialiseGame();

				return;
			}
		}
		else {
			level2Button->scaling.x = 1.50f;
			level2Button->scaling.y = 1.50f;
		}

		//collision detection of mouse cursor with the quit game button
		if (CollisionDetection(mouseCursor->colRect, quitGameButton->colRect))
		{
			quitGameButton->scaling.x = 1.55f;
			quitGameButton->scaling.y = 1.55f;


			if (DirectInputManager::mouseState.rgbButtons[0] & 0x80) {
				AudioManager::PlaySelectSound();

				PostQuitMessage(0);
			}
		}
		else {
			quitGameButton->scaling.x = 1.5f;
			quitGameButton->scaling.y = 1.5f;
		}

		// collision detection of mouse cursor with the mute volume button
		if (circleCollisionDetection(mouseCursor->spriteWidth * mouseCursor->scaling.x / 2, muteButton->spriteWidth * muteButton->scaling.x / 2 * 0.7, mouseCursor->pos + mouseCursor->spriteCenter, muteButton->pos + muteButton->spriteCenter))
		{
			muteButton->scaling.x = 1.10f;
			muteButton->scaling.y = 1.10f;

			// volume = 0
			if (DirectInputManager::mouseState.rgbButtons[0] & 0x80) {
				AudioManager::isMuted = true;

				if (AudioManager::bgmChannel != nullptr)
				{
					AudioManager::bgmChannel->setVolume(0.0f);
				}

				volume = 0;
			}
		}
		else {
			muteButton->scaling.x = 1.0f;
			muteButton->scaling.y = 1.0f;
		}

		// collision detection of mouse cursor with the minus volume button
		if (circleCollisionDetection(mouseCursor->spriteWidth * mouseCursor->scaling.x / 2, minusButton->spriteWidth * minusButton->scaling.x / 2 * 0.7, mouseCursor->pos + mouseCursor->spriteCenter, minusButton->pos + minusButton->spriteCenter))
		{
			minusButton->scaling.x = 1.10f;
			minusButton->scaling.y = 1.10f;

			if (DirectInputManager::mouseState.rgbButtons[0] & 0x80) {
				AudioManager::isMuted = false;
				AudioManager::SOUND_VOLUME -= 0.02f;

				if (AudioManager::SOUND_VOLUME < 0.0f)
				{
					AudioManager::SOUND_VOLUME = 0.0f;
				}

				AudioManager::VolumeControl(AudioManager::SOUND_VOLUME);

				volume = (int)(AudioManager::SOUND_VOLUME * 100);
			}
		}
		else {
			minusButton->scaling.x = 1.0f;
			minusButton->scaling.y = 1.0f;
		}

		// collision detection of mouse cursor with the add volume button
		if (circleCollisionDetection(mouseCursor->spriteWidth * mouseCursor->scaling.x / 2, addButton->spriteWidth * addButton->scaling.x / 2 * 0.7, mouseCursor->pos + mouseCursor->spriteCenter, addButton->pos + addButton->spriteCenter))
		{
			addButton->scaling.x = 1.10f;
			addButton->scaling.y = 1.10f;

			if (DirectInputManager::mouseState.rgbButtons[0] & 0x80) {
				AudioManager::isMuted = false;
				AudioManager::SOUND_VOLUME += 0.02f;

				if (AudioManager::SOUND_VOLUME > 1.0f)
				{
					AudioManager::SOUND_VOLUME = 1.0f;
				}

				AudioManager::VolumeControl(AudioManager::SOUND_VOLUME);

				volume = (int)(AudioManager::SOUND_VOLUME * 100);
			}
		}
		else {
			addButton->scaling.x = 1.0f;
			addButton->scaling.y = 1.0f;
		}

		// collision detection of mouse cursor with the unmute volume button
		if (circleCollisionDetection(mouseCursor->spriteWidth * mouseCursor->scaling.x / 2, unmuteButton->spriteWidth * unmuteButton->scaling.x / 2 * 0.7, mouseCursor->pos + mouseCursor->spriteCenter, unmuteButton->pos + unmuteButton->spriteCenter))
		{
			unmuteButton->scaling.x = 1.10f;
			unmuteButton->scaling.y = 1.10f;

			if (DirectInputManager::mouseState.rgbButtons[0] & 0x80) {
				AudioManager::isMuted = false;
				AudioManager::VolumeControl(AudioManager::SOUND_VOLUME);

				// Restore displayed volume
				volume = (int)(AudioManager::SOUND_VOLUME * 100);
			}
		}
		else {
			unmuteButton->scaling.x = 1.0f;
			unmuteButton->scaling.y = 1.0f;
		}
	}

	if (DirectInputManager::diKeys[DIK_ESCAPE] & 0x80) {
		PostQuitMessage(0);
	}
}

void MainMenu::Render()
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

	for (GameObject* gameObject:gameObject)
	{
		D3DXVECTOR2* scalingCenter = NULL;

		if (gameObject == level1Button || gameObject == level2Button || gameObject == quitGameButton ||
			gameObject == muteButton || gameObject == minusButton || gameObject == addButton ||
			gameObject == unmuteButton)
		{
			scalingCenter = &gameObject->spriteCenter;
		}
		
		D3DXMatrixTransformation2D(&gameObject->mat, scalingCenter, 0.0, &gameObject->scaling, &gameObject->spriteCenter, gameObject->rotation, &gameObject->pos);

		DirectXManager::spriteBrush->SetTransform(&gameObject->mat);

		if (gameObject == gameTitle)
		{
			DirectXManager::spriteBrush->Draw(gameObject->texture, &gameObject->titleRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
		}
		else
		{
			DirectXManager::spriteBrush->Draw(gameObject->texture, &gameObject->animRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
		}

	}

	DirectXManager::spriteBrush->End();

	RECT volumeRect;
	volumeRect.left = 0;
	volumeRect.top = 970;
	volumeRect.right = WindowManager::ScreenWidth;
	volumeRect.bottom = 1035;

	string volumeText = to_string(volume);

	DirectXManager::font->DrawText(NULL, volumeText.c_str(), -1, &volumeRect, DT_CENTER, D3DCOLOR_XRGB(255, 255, 255)
	);

	DirectXManager::myVirtualGPU->EndScene();
	DirectXManager::myVirtualGPU->Present(NULL, NULL, NULL, NULL);
}

void MainMenu::CleanUp()
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

	gameTitle = nullptr;
	level1Button = nullptr;
	level2Button = nullptr;
	quitGameButton = nullptr;
	muteButton = nullptr;
	minusButton = nullptr;
	addButton = nullptr;
	unmuteButton = nullptr;
	mouseCursor = nullptr;
}

MainMenu::MainMenu()
{}