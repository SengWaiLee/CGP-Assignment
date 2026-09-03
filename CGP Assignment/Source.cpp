#include "WindowManager.h"
#include "DirectXManager.h"
#include "AudioManager.h"
#include "DirectInputManager.h"
#include "MainMenu.h"
#include "Game.h"

using namespace std;

#define WIN32_LEAN_AND_MEAN

int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	WindowManager* gameWindowManager = new WindowManager();
	DirectXManager* directX = new DirectXManager();
	AudioManager* gameAudio = new AudioManager();
	DirectInputManager* directInput = new DirectInputManager();

	Game::gameStack.push_back(new MainMenu());

	gameAudio->InitialiseAudio();
	gameAudio->LoadSound();

	Game::gameStack.back()->InitialiseGame();

	while (gameWindowManager->WindowIsRunning())
	{
		directInput->GettingInput();

		Game::gameStack.back()->Update();
		Game::gameStack.back()->Render();

		gameAudio->updateSound();
	}

	// Clean up and delete all remaining game states
	while (!Game::gameStack.empty())
	{
		Game* currentGame = Game::gameStack.back();

		currentGame->CleanUp();
		Game::gameStack.pop_back();

		delete currentGame;
		currentGame = nullptr;
	}

	gameWindowManager->CleanUpWindow();
	directX->CleanUpDirectX();
	directInput->CleanUpDirectInput();

	return 0;
}