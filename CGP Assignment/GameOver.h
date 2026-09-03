#pragma once
#include "Game.h"
#include "DirectInputManager.h"
#include "AudioManager.h"
#include "MainMenu.h"
#include "level1.h"
#include "ParallaxLayer.h"

class GameOver : public Game
{
public:
	ParallaxLayer NebulaBG;
	ParallaxLayer FarStarsBG;
	ParallaxLayer MiddleStarsBG;
	ParallaxLayer PlanetBG;
	ParallaxLayer DenseStarsBG;
	ParallaxLayer NearStarsBG;

	ParallaxLayer AsteroidBG1;
	ParallaxLayer AsteroidBG2;

	GameObject* gameOver;
	GameObject* replayButton;
	GameObject* mainMenuButton;
	GameObject* mouseCursor;
	GameObject* previousHoveredButton = nullptr;

	void InitialiseGame() override;
	void Update() override;
	void Render() override;
	void CleanUp() override;

	GameOver();
};