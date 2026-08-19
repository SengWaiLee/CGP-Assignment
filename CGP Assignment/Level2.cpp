#include "Level2.h"

void Level2::InitialiseGame()
{
	GameObject* bg = new GameObject((LPSTR)"level1bg.png", 1, 1, 1920, 1080, 0, 1, 1, 0, 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
	gameObject.push_back(bg);

	GameObject* space1ship1 = new GameObject((LPSTR)"spaceship.png", 2, 2, 64, 64, 0, 2, 1, 5, 20, D3DXVECTOR2(500.0f, 500.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
	gameObject.push_back(space1ship1);

	GameObject* space1ship2 = new GameObject((LPSTR)"spaceship.png", 2, 2, 64, 64, 1, 2, 1, 5, 1, D3DXVECTOR2(300.0f, 500.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
	gameObject.push_back(space1ship2);
}

void Level2::Update()
{
	spaceship1 = gameObject.at(1);
	spaceship2 = gameObject.at(2);

	for (int i = 0; i < frameTimer->framesToUpdate(); i++)
	{
		spaceship1->engineForce.x = 0;
		spaceship1->engineForce.y = 0;
		spaceship1->accel.x = 0;
		spaceship1->accel.y = 0;
		spaceship2->accel.x = 0;
		spaceship2->accel.y = 0;


		spaceship1->animRect.top = spaceship1->currentFrame % spaceship1->maxFrame % spaceship1->row * spaceship1->spriteHeight;
		spaceship1->animRect.bottom = spaceship1->animRect.top + spaceship1->spriteHeight;
		spaceship1->animRect.left = spaceship1->direction * spaceship1->spriteWidth;
		spaceship1->animRect.right = spaceship1->animRect.left + spaceship1->spriteWidth;

		spaceship2->animRect.top = spaceship2->currentFrame % spaceship2->maxFrame % spaceship2->row * spaceship2->spriteHeight;
		spaceship2->animRect.bottom = spaceship2->animRect.top + spaceship2->spriteHeight;
		spaceship2->animRect.left = spaceship2->direction * spaceship2->spriteWidth;
		spaceship2->animRect.right = spaceship2->animRect.left + spaceship2->spriteWidth;

		spaceship1->currentFrame++;
		spaceship2->currentFrame++;

		if (DirectInputManager::diKeys[DIK_W] & 0x80) {
			spaceship1->engineForce.x = spaceship1->speed * sin(spaceship1->rotation);
			spaceship1->engineForce.y = spaceship1->speed * -cos(spaceship1->rotation);
			spaceship1->accel = spaceship1->engineForce / spaceship1->mass;
		}

		if (DirectInputManager::diKeys[DIK_A] & 0x80) {
			spaceship1->rotation -= 0.25;
		}
		if (DirectInputManager::diKeys[DIK_D] & 0x80) {
			spaceship1->rotation += 0.25;
		}

		if (DirectInputManager::diKeys[DIK_UP] & 0x80) {
			spaceship2->engineForce.x = spaceship2->speed * sin(spaceship2->rotation);
			spaceship2->engineForce.y = spaceship2->speed * -cos(spaceship2->rotation);
			spaceship2->accel = spaceship2->engineForce / spaceship2->mass;
		}

		if (DirectInputManager::diKeys[DIK_S] & 0x80) {
			spaceship1->vel.x = 0;
			spaceship1->vel.y = 0;
			spaceship2->vel.x = 0;
			spaceship2->vel.y = 0;
		}

		if (DirectInputManager::diKeys[DIK_B] & 0x80) {
			Game::gameStack.back()->CleanUp();
			Game::gameStack.pop_back();
		}

		if (circleCollisionDetection(spaceship1->spriteWidth / 2, spaceship2->spriteWidth / 2, spaceship1->pos, spaceship2->pos)) {

			//find collision normal
			D3DXVECTOR2 colNormal = spaceship2->pos - spaceship1->pos;
			D3DXVec2Normalize(&colNormal, &colNormal);
			//calculate the bounce vector using the collision normal
			D3DXVECTOR2 velNormal = colNormal * D3DXVec2Dot(&spaceship1->vel, &colNormal);
			D3DXVECTOR2 velTangent = spaceship1->vel - velNormal;
			D3DXVECTOR2 velBounce = velTangent - velNormal;

			spaceship1->accel = velBounce / spaceship1->mass;
			spaceship2->accel = -velBounce / spaceship2->mass;
			cout << "collied" << endl;

		}


		//space boundary1
		if (spaceship1->pos.y < 0 || spaceship1->pos.y > 1000 - spaceship1->spriteHeight) {
			spaceship1->vel.y *= -1;
		}
		if (spaceship1->pos.x < 0 || spaceship1->pos.x > 1900 - spaceship1->spriteWidth) {
			spaceship1->vel.x *= -1;
		}

		//space boundary2
		if (spaceship2->pos.y < 0 || spaceship2->pos.y > 1000 - spaceship2->spriteHeight) {
			spaceship2->vel.y *= -1;
		}
		if (spaceship2->pos.x < 0 || spaceship2->pos.x > 1900 - spaceship2->spriteWidth) {
			spaceship2->vel.x *= -1;
		}

		spaceship1->vel += spaceship1->accel;
		spaceship2->vel += spaceship2->accel;

		spaceship1->pos += spaceship1->vel;
		spaceship2->pos += spaceship2->vel;

	}
}

void Level2::CleanUp()
{
	for (GameObject* gameObject : gameObject) {
		gameObject->texture->Release();
		gameObject->texture = NULL;
	}
	gameObject.clear();
}

Level2::Level2()
{}