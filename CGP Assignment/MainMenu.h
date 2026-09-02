#pragma once
#include "Game.h"
#include "DirectInputManager.h"
#include "GameObject.h"
#include "AudioManager.h"
#include <vector>
#include "Level1.h"
#include "Level2.h"
#include "ParallaxLayer.h"
#include <Windows.h>

class MainMenu :    public Game
{
private:

    ParallaxLayer NebulaBG;
    ParallaxLayer FarStarsBG;
    ParallaxLayer MiddleStarsBG;
    ParallaxLayer PlanetBG;
    ParallaxLayer DenseStarsBG;
    ParallaxLayer NearStarsBG;

    ParallaxLayer AsteroidBG1;
    ParallaxLayer AsteroidBG2;

public:
    GameObject* gameTitle = nullptr;
    GameObject* level1Button = nullptr;
    GameObject* level2Button = nullptr;
    GameObject* quitGameButton = nullptr;

    GameObject* muteButton = nullptr;
    GameObject* minusButton = nullptr;
    GameObject* addButton = nullptr;
    GameObject* unmuteButton = nullptr;

    GameObject* mouseCursor = nullptr;

    int volume = 100;

    MainMenu();

    void InitialiseGame() override;

    void Update() override;

	void Render() override;

    void CleanUp() override;
    
};

