#pragma once
#include "Game.h"
#include "DirectInputManager.h"
#include "AudioManager.h"
#include "MainMenu.h"
#include "level1.h"
class GameOver : public Game
{
public:
	void Update();
	void InitialiseGame();
	void CleanUp();
	GameOver();
	GameObject* replayButton;
	GameObject* replayText;
	GameObject* mainMenuButton;
	GameObject* mainMenuText;

	GameObject* mouseCursor;
};