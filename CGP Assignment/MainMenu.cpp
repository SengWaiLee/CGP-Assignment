#include "MainMenu.h"
#include <iostream>
using namespace std;

void MainMenu::Update()
{
	level1Button = gameObject.at(2);
	level2Button = gameObject.at(3);
	quitGameButton = gameObject.at(4);
	muteButton = gameObject.at(5);
	minusButton = gameObject.at(6);
	addButton = gameObject.at(7);
	unmuteButton = gameObject.at(8);
	mouseCursor = gameObject.at(9);

	for (int i = 0; i < frameTimer->framesToUpdate(); i++)
	{
		//update mouse cursor position
		mouseCursor->pos.x += DirectInputManager::mouseState.lX * 5.0;
		mouseCursor->pos.y += DirectInputManager::mouseState.lY * 5.0;

		// collision detection of mouse cursor with the level 1 button
		if (CollisionDetection(level1Button->colRect, mouseCursor->colRect))
		{
			level1Button->scaling.x = 1.55f;
			level1Button->scaling.y = 1.55f;

			if (DirectInputManager::mouseState.rgbButtons[0] & 0x80) {
				Game::gameStack.push_back(new Level1());
				Game::gameStack.back()->InitialiseGame();
				break;
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

			if (DirectInputManager::mouseState.rgbButtons[0] & 0x80) {
				Game::gameStack.push_back(new Level2());
				Game::gameStack.back()->InitialiseGame();
				break;
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
				isMuted = true;
				AudioManager::bgmChannel->setVolume(0);
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
				AudioManager::SOUND_VOLUME -= 0.01f;
				AudioManager::VolumeControl(AudioManager::SOUND_VOLUME);
			}
		}
		else {
			minusButton->scaling.x = 1.0f;
			minusButton->scaling.y = 1.0f;
		}

		// collision detection of mouse cursor with the add volume button
		if (circleCollisionDetection(mouseCursor->spriteWidth * mouseCursor->scaling.x / 2, addButton->spriteWidth * addButton->scaling.x / 2 * 0.7, mouseCursor->pos + mouseCursor->spriteCenter, addButton->pos + minusButton->spriteCenter))
		{
			addButton->scaling.x = 1.10f;
			addButton->scaling.y = 1.10f;

			if (DirectInputManager::mouseState.rgbButtons[0] & 0x80) {
				AudioManager::SOUND_VOLUME += 0.01f;
				AudioManager::VolumeControl(AudioManager::SOUND_VOLUME);
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
				AudioManager::VolumeControl(AudioManager::SOUND_VOLUME);
				isMuted = false;
			}
		}
		else {
			unmuteButton->scaling.x = 1.0f;
			unmuteButton->scaling.y = 1.0f;
		}

		mouseCursor->colRect.top = mouseCursor->pos.y;
		mouseCursor->colRect.bottom = mouseCursor->colRect.top + ((float)mouseCursor->spriteHeight * mouseCursor->scaling.y);
		mouseCursor->colRect.left = mouseCursor->pos.x;
		mouseCursor->colRect.right = mouseCursor->colRect.left + ((float)mouseCursor->spriteWidth * mouseCursor->scaling.x);

		//Mouse Boundary
		//up
		if (mouseCursor->pos.y < 0)
		{
			mouseCursor->pos.y = 0;
		}
		//down
		if (mouseCursor->pos.y > WindowManager::ScreenHeight - mouseCursor->spriteHeight * mouseCursor->scaling.y)
		{
			mouseCursor->pos.y = WindowManager::ScreenHeight - mouseCursor->spriteHeight * mouseCursor->scaling.y;
		}
		//right
		if (mouseCursor->pos.x > WindowManager::ScreenWidth - mouseCursor->spriteWidth * mouseCursor->scaling.x)
		{
			mouseCursor->pos.x = WindowManager::ScreenWidth - mouseCursor->spriteWidth * mouseCursor->scaling.x;
		}
		//left
		if (mouseCursor->pos.x < 0)
		{
			mouseCursor->pos.x = 0;
		}
	}

	if (DirectInputManager::diKeys[DIK_ESCAPE] & 0x80) {
		PostQuitMessage(0);
	}
}

void MainMenu::CleanUp()
{
	for (GameObject* gameObject : gameObject) {
		gameObject->texture->Release();
		gameObject->texture = NULL;
	}
	gameObject.clear();
}

void MainMenu::InitialiseGame()
{
	//Initialize texture(background, game title), button(startgame, exitgame), mouse cursor
	if (!isMuted) {
		AudioManager::PlayMainMenuSound();
	}
	GameObject* background = new GameObject((LPSTR)"background.png", 1, 1, 1920, 1080, 0, 1, 1, 0, 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
	gameObject.push_back(background);
	GameObject* gameTitle = new GameObject((LPSTR)"gametitle.png", 1, 1, 512, 109, 0, 1, 1, 0, 0, D3DXVECTOR2(450.0f, 80.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(2.0f, 2.0f));
	gameObject.push_back(gameTitle);
	GameObject* level1Button = new GameObject((LPSTR)"level1button.png", 1, 1, 256, 128, 0, 1, 1, 0, 0, D3DXVECTOR2(795.0f, 300.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.5f, 1.5f));
	gameObject.push_back(level1Button);
	GameObject* level2Button = new GameObject((LPSTR)"level2button.png", 1, 1, 256, 128, 0, 1, 1, 0, 0, D3DXVECTOR2(795.0f, 500.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.5f, 1.5f));
	gameObject.push_back(level2Button);
	GameObject* quitGameButton = new GameObject((LPSTR)"quitgamebutton.png", 1, 1, 256, 128, 0, 1, 1, 0, 0, D3DXVECTOR2(795.0f, 700.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.5f, 1.5f));
	gameObject.push_back(quitGameButton);
	GameObject* muteButton = new GameObject((LPSTR)"mutebutton.png", 1, 1, 64, 64, 0, 1, 1, 0, 0, D3DXVECTOR2(695.0f, 900.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
	gameObject.push_back(muteButton);
	GameObject* minusButton = new GameObject((LPSTR)"minusbutton.png", 1, 1, 64, 64, 0, 1, 1, 0, 0, D3DXVECTOR2(805.0f, 900.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
	gameObject.push_back(minusButton);
	GameObject* addButton = new GameObject((LPSTR)"addbutton.png", 1, 1, 64, 64, 0, 1, 1, 0, 0, D3DXVECTOR2(1115.0f, 900.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
	gameObject.push_back(addButton);
	GameObject* unmuteButton = new GameObject((LPSTR)"unmutebutton.png", 1, 1, 64, 64, 0, 1, 1, 0, 0, D3DXVECTOR2(1225.0f, 900.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
	gameObject.push_back(unmuteButton);
	GameObject* mouseCursor = new GameObject((LPSTR)"pointer.png", 1, 1, 32, 32, 0, 1, 1, 0, 0, D3DXVECTOR2(700.0f, 500.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(2.0f, 2.0f));
	gameObject.push_back(mouseCursor);
}

MainMenu::MainMenu()
{}