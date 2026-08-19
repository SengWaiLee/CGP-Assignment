#pragma once
#include "Game.h"
#include "DirectInputManager.h"
#include "GameObject.h"
#include "AudioManager.h"
#include "MainMenu.h"
#include "Level2.h"
#include "GameOver.h"
class Level1 :
    public Game
{
public:
    GameObject* platform5;
    GameObject* platform4;
    GameObject* platform3;
    GameObject* platform2;
    GameObject* platform;
    GameObject* destination;
    GameObject* militia;
    bool canJump;
    bool playLandSound = false;
    void InitialiseGame();
    void Update();
    void CleanUp();
    float gravity;
    float friction;
    Level1();
};