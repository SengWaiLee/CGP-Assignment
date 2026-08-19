#include "GameOver.h"

void GameOver::Update()
{
	for (int i = 0; i < frameTimer->framesToUpdate(); i++)
	{
		replayButton = gameObject.at(2);
		replayText = gameObject.at(3);
		mainMenuButton = gameObject.at(4);
		mainMenuText = gameObject.at(5);
		mouseCursor = gameObject.at(6);

		//update mouse cursor position
		mouseCursor->pos.x += DirectInputManager::mouseState.lX * 5.0;
		mouseCursor->pos.y += DirectInputManager::mouseState.lY * 5.0;

		// collision detection of mouse cursor with the replay
		if (CollisionDetection(replayButton->colRect, mouseCursor->colRect))
		{
			replayButton->scaling.x = 1.55f;
			replayButton->scaling.y = 1.55f;

			replayText->scaling.x = 1.05f;
			replayText->scaling.y = 1.05f;

			if (DirectInputManager::mouseState.rgbButtons[0] & 0x80) {
				Game::gameStack.pop_back();
				Game::gameStack.push_back(new Level1());
				Game::gameStack.back()->InitialiseGame();
			}


		}
		else {
			replayButton->scaling.x = 1.50f;
			replayButton->scaling.y = 1.50f;

			replayText->scaling.x = 1.0f;
			replayText->scaling.y = 1.0f;

		}

		//collision detection of mouse cursor with the mainMenu button
		if (CollisionDetection(mouseCursor->colRect, mainMenuButton->colRect))
		{
			mainMenuButton->scaling.x = 1.55f;
			mainMenuButton->scaling.y = 1.55f;

			mainMenuText->scaling.x = 1.55f;
			mainMenuText->scaling.y = 1.55f;


			if (DirectInputManager::mouseState.rgbButtons[0] & 0x80) {
				AudioManager::PlaySelectSounds();
				Game::gameStack.pop_back();
				Game::gameStack.push_back(new MainMenu());
				Game::gameStack.back()->InitialiseGame();
				this->CleanUp();
				break;


			}
		}
		else {
			mainMenuButton->scaling.x = 1.5f;
			mainMenuButton->scaling.y = 1.5f;

			mainMenuText->scaling.x = 1.5f;
			mainMenuText->scaling.y = 1.5f;
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

}

void GameOver::InitialiseGame()
{
	//initialize texture(background,game over), button(exit, retry), mouse cursor
	AudioManager::PlayVictorySounds();
	GameObject* background = new GameObject((LPSTR)"background.png", 1, 1, 1920, 1080, 0, 1, 1, 0, 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
	gameObject.push_back(background);
	GameObject* gameOver = new GameObject((LPSTR)"victory.png", 1, 1, 512, 256, 0, 1, 1, 0, 0, D3DXVECTOR2(450.0f, 100.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(2.0f, 2.0f));
	gameObject.push_back(gameOver);
	GameObject* replayButton = new GameObject((LPSTR)"button.png", 1, 1, 256, 128, 0, 1, 1, 0, 0, D3DXVECTOR2(795.0f, 500.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.5f, 1.5f));
	gameObject.push_back(replayButton);
	GameObject* replayText = new GameObject((LPSTR)"replay.png", 1, 1, 256, 128, 0, 1, 1, 0, 0, D3DXVECTOR2(855.0f, 525.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
	gameObject.push_back(replayText);
	GameObject* mainMenuButton = new GameObject((LPSTR)"button.png", 1, 1, 256, 128, 0, 1, 1, 0, 0, D3DXVECTOR2(795.0f, 700.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.5f, 1.5f));
	gameObject.push_back(mainMenuButton);
	GameObject* mainMenuText = new GameObject((LPSTR)"mainMenu.png", 1, 1, 256, 128, 0, 1, 1, 0, 0, D3DXVECTOR2(795.0f, 695.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.5f, 1.5f));
	gameObject.push_back(mainMenuText);
	GameObject* mouseCursor = new GameObject((LPSTR)"pointer.png", 1, 1, 32, 32, 0, 1, 1, 0, 0, D3DXVECTOR2(700.0f, 500.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(2.0f, 2.0f));
	gameObject.push_back(mouseCursor);

}

void GameOver::CleanUp()
{
	for (GameObject* gameObject : gameObject) {
		gameObject->texture->Release();
		gameObject->texture = NULL;
	}
	gameObject.clear();
}

GameOver::GameOver()
{}