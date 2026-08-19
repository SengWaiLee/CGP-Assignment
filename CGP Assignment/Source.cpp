#include "WindowManager.h"
#include "DirectXManager.h"
#include "AudioManager.h"
#include "DirectInputManager.h"
#include "MainMenu.h"
#include "Game.h"
#include "FrameTimer.h"
#include "Level1.h"
#include "Level2.h"
#include <iostream>

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
	gameAudio->LoadSounds();
	Game::gameStack.back()->InitialiseGame();
	while (gameWindowManager->WindowIsRunning())
	{
		directInput->GettingInput();
		Game::gameStack.back()->Update();
		Game::gameStack.back()->Render();
	}
	Game::gameStack.back()->CleanUp();
	Game::gameStack.clear();
	gameWindowManager->CleanUpWindow();
	directX->CleanUpDirectX();
	directInput->CleanUpDirectInput();
	return 0;
}