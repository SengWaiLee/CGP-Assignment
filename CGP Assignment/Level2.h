#pragma once
#include "Game.h"
#include "DirectInputManager.h"
#include "MainMenu.h"

class Level2 :
    public Game
{
public:
    float friction = 0.9f;
    GameObject* bg;
    GameObject* spaceship1;
    GameObject* spaceship2;
    void InitialiseGame();
    void Update();
    void RenderText();
    void CleanUp();
    Level2();
};