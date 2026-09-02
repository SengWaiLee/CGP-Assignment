#pragma once
#include "Game.h"
#include "DirectInputManager.h"
#include "GameObject.h"
#include "AudioManager.h"
#include <vector>
#include "Level1.h"
#include "Level2.h"
#include <Windows.h>

class MainMenu :
    public Game
{
public:
    GameObject* level1Button;
    GameObject* level2Button;
    GameObject* quitGameButton;
    GameObject* muteButton;
    GameObject* minusButton;
    GameObject* addButton;
    GameObject* unmuteButton;
    GameObject* mouseCursor;
    int volume = 100;
    void InitialiseGame();
    void Update();
	void Render();
    void CleanUp();
    MainMenu();
};

