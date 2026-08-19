#include "Level1.h"
AudioManager* audio = new AudioManager;
void Level1::InitialiseGame()
{
	friction = 0.9f;
	gravity = 9.8f;
	GameObject* bg = new GameObject((LPSTR)"level1bg.png", 1, 1, 1920, 1080, 0, 1, 1, 0, 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
	gameObject.push_back(bg);


	GameObject* platform5 = new GameObject((LPSTR)"platform.png", 1, 1, 2048, 925, 0, 1, 1, 0, 0, D3DXVECTOR2(1500.0f, 525.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.03f, 0.01f));
	gameObject.push_back(platform5);

	GameObject* platform4 = new GameObject((LPSTR)"platform.png", 1, 1, 2048, 925, 0, 1, 1, 0, 0, D3DXVECTOR2(950.0f, 400.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.2f, 0.01f));
	gameObject.push_back(platform4);

	GameObject* platform3 = new GameObject((LPSTR)"platform.png", 1, 1, 2048, 925, 0, 1, 1, 0, 0, D3DXVECTOR2(1250.0f, 625.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.025f, 0.01f));
	gameObject.push_back(platform3);

	GameObject* platform2 = new GameObject((LPSTR)"platform.png", 1, 1, 2048, 925, 0, 1, 1, 0, 0, D3DXVECTOR2(800.0f, 725.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.1f, 0.01f));
	gameObject.push_back(platform2);

	GameObject* platform = new GameObject((LPSTR)"platform.png", 1, 1, 2048, 925, 0, 1, 1, 0, 0, D3DXVECTOR2(500.0f, 850.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.07f, 0.01f));
	gameObject.push_back(platform);

	GameObject* destination = new GameObject((LPSTR)"flag.png", 1, 5, 300, 60, 0, 5, 0, 0, 0, D3DXVECTOR2(950.0f, 330.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
	gameObject.push_back(destination);

	GameObject* militia = new GameObject((LPSTR)"militia.png", 4, 4, 128, 192, 2, 4, 0, 25, 10, D3DXVECTOR2(0.0f, 100.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 555, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(2.0f, 2.0f));
	gameObject.push_back(militia);
	/*audio->PlayLvl1Bgm();*/
}

void Level1::Update()
{
	platform5 = gameObject.at(1);
	platform4 = gameObject.at(2);
	platform3 = gameObject.at(3);
	platform2 = gameObject.at(4);
	platform = gameObject.at(5);
	destination = gameObject.at(6);
	militia = gameObject.at(7);

	for (int i = 0; i < frameTimer->framesToUpdate(); i++)
	{

		destination->currentFrame++;
		//update militia animation rectangle
		militia->animRect.top = militia->direction * militia->spriteHeight;
		militia->animRect.bottom = militia->animRect.top + militia->spriteHeight;
		militia->animRect.left = militia->currentFrame % militia->maxFrame % militia->col * militia->spriteWidth;
		militia->animRect.right = militia->animRect.left + militia->spriteWidth;

		//update destination animation rectangle
		destination->animRect.top = destination->direction * destination->spriteHeight;
		destination->animRect.bottom = destination->animRect.top + destination->spriteHeight;
		destination->animRect.left = destination->currentFrame % destination->maxFrame % destination->col * destination->spriteWidth;
		destination->animRect.right = destination->animRect.left + destination->spriteWidth;

		//adding frictional and gravitational force to militia
		militia->vel.x *= friction;
		militia->vel.y += gravity;

		//collision detection between player and the platform
		if (CollisionDetection(militia->colRect, platform->colRect)) {
			if (playLandSound) {
				AudioManager::PlayLandSound();
				playLandSound = false;
			}
			militia->vel.y = 0;
			if (militia->colRect.bottom > platform->colRect.top) {
				cout << "collied top" << endl;

				militia->pos.y -= (militia->colRect.bottom - platform->colRect.top);
				canJump = true;
			}


		}

		//collision detection between player and the platform
		if (CollisionDetection(militia->colRect, platform2->colRect)) {
			if (playLandSound) {
				AudioManager::PlayLandSound();
				playLandSound = false;
			}
			militia->vel.y = 0;
			if (militia->colRect.bottom > platform2->colRect.top) {
				cout << "collied top" << endl;
				militia->pos.y -= (militia->colRect.bottom - platform2->colRect.top);
				canJump = true;
			}


		}

		//collision detection between player and the platform
		if (CollisionDetection(militia->colRect, platform3->colRect)) {
			if (playLandSound) {
				AudioManager::PlayLandSound();
				playLandSound = false;
			}
			militia->vel.y = 0;
			if (militia->colRect.bottom > platform3->colRect.top) {
				cout << "collied top" << endl;
				militia->pos.y -= (militia->colRect.bottom - platform3->colRect.top);
				canJump = true;
			}

		}

		//collision detection between player and the platform
		if (CollisionDetection(militia->colRect, platform4->colRect)) {
			if (playLandSound) {
				AudioManager::PlayLandSound();
				playLandSound = false;
			}
			militia->vel.y = 0;
			if (militia->colRect.bottom > platform4->colRect.top) {
				cout << "collied top" << endl;
				militia->pos.y -= (militia->colRect.bottom - platform4->colRect.top);
				canJump = true;
			}


		}

		//collision detection between player and the platform
		if (CollisionDetection(militia->colRect, platform5->colRect)) {
			if (playLandSound) {
				AudioManager::PlayLandSound();
				playLandSound = false;
			}
			militia->vel.y = 0;
			if (militia->colRect.bottom > platform5->colRect.top) {
				cout << "collied top" << endl;
				militia->pos.y -= (militia->colRect.bottom - platform5->colRect.top);
				canJump = true;
			}


		}

		//collision detection between player and the destination
		if (CollisionDetection(militia->colRect, destination->colRect)) {
			cout << "won" << endl;
			Game::gameStack.pop_back();
			Game::gameStack.push_back(new GameOver());
			Game::gameStack.back()->InitialiseGame();
			//this->CleanUp();
		}

		//checking input for space bar
		if (DirectInputManager::diKeys[DIK_SPACE] & 0x80) {
			if (canJump == true) {
				AudioManager::PlayJumpSound();
				militia->jumpAccel.y = militia->jumpForce / militia->mass;
				militia->vel -= militia->jumpAccel;
				canJump = false;
				playLandSound = true;
			}
		}

		//checking input for d key
		if (DirectInputManager::diKeys[DIK_D] & 0x80) {
			militia->direction = 2;
			militia->currentFrame++;
			militia->accel.x = militia->speed / militia->mass;
			militia->vel += militia->accel;
		}

		//checking input for a key
		if (DirectInputManager::diKeys[DIK_A] & 0x80) {
			militia->direction = 1;
			militia->currentFrame++;
			militia->accel.x = militia->speed / militia->mass;
			militia->vel -= militia->accel;
		}

		//updating position
		militia->pos += militia->vel;


		//update collision rectangle
		militia->colRect.top = militia->pos.y;
		militia->colRect.bottom = militia->colRect.top + (float)militia->spriteHeight * militia->scaling.y;
		militia->colRect.left = militia->pos.x;
		militia->colRect.right = militia->colRect.left + (float)militia->spriteWidth * militia->scaling.x;

		//militia boundary 
		if (militia->pos.y > 950 - militia->spriteHeight) {
			militia->pos.y = 950 - militia->spriteHeight;
			if (playLandSound) {
				AudioManager::PlayLandSound();
				playLandSound = false;
			}

			canJump = true;
			militia->vel.y = 0;
		}
		if (militia->pos.y < 0) {
			militia->pos.y = 0;
		}
		if (militia->pos.x > 1900 - militia->spriteWidth) {
			militia->pos.x = 1900 - militia->spriteWidth;
		}
		if (militia->pos.x < 0) {
			militia->pos.x = 0;
		}
		if (DirectInputManager::diKeys[DIK_B] & 0x80) {
			Game::gameStack.back()->CleanUp();
			Game::gameStack.pop_back();
		}
	}
}

void Level1::CleanUp()
{
	for (GameObject* gameObject : gameObject) {
		gameObject->texture->Release();
		gameObject->texture = NULL;
	}
	gameObject.clear();

}

Level1::Level1()
{}