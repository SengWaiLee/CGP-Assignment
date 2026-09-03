#include "Level2.h"
#include <string>
#include <sstream>
#include <iomanip>

void Level2::InitialiseGame()
{
	AudioManager::PlayLevel2Sound();
	
	bg = new GameObject((LPSTR)"Assets/level2bg.png", 1, 1, 1920, 1080, 0, 1, 1, 0, 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
	gameObject.push_back(bg);

	spaceship1 = new GameObject((LPSTR)"Assets/spaceship.png", 2, 2, 64, 64, 0, 2, 1, 5, 20, D3DXVECTOR2(500.0f, 500.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
	gameObject.push_back(spaceship1);

	spaceship2 = new GameObject((LPSTR)"Assets/spaceship.png", 2, 2, 64, 64, 1, 2, 1, 5, 5, D3DXVECTOR2(300.0f, 500.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
	gameObject.push_back(spaceship2);
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

		spaceship2->engineForce.x = 0;
		spaceship2->engineForce.y = 0;
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

		if (DirectInputManager::diKeys[DIK_W] & 0x80) 
		{
			spaceship1->engineForce.x = spaceship1->speed * sin(spaceship1->rotation);
			spaceship1->engineForce.y = spaceship1->speed * -cos(spaceship1->rotation);
			spaceship1->accel = spaceship1->engineForce / spaceship1->mass;
		}

		if (DirectInputManager::diKeys[DIK_A] & 0x80) 
		{
			spaceship1->rotation -= 0.25;
		}
		if (DirectInputManager::diKeys[DIK_D] & 0x80) 
		{
			spaceship1->rotation += 0.25;
		}

		if (DirectInputManager::diKeys[DIK_S] & 0x80)
		{
			spaceship1->vel.x = 0;
			spaceship1->vel.y = 0;

			spaceship1->accel.x = 0;
			spaceship1->accel.y = 0;

			spaceship1->engineForce.x = 0;
			spaceship1->engineForce.y = 0;
		}

		if (DirectInputManager::diKeys[DIK_UP] & 0x80) 
		{
			spaceship2->engineForce.x = spaceship2->speed * sin(spaceship2->rotation);
			spaceship2->engineForce.y = spaceship2->speed * -cos(spaceship2->rotation);
			spaceship2->accel = spaceship2->engineForce / spaceship2->mass;
		}

		if (DirectInputManager::diKeys[DIK_LEFT] & 0x80)
		{
			spaceship2->rotation -= 0.25f;
		}

		if (DirectInputManager::diKeys[DIK_RIGHT] & 0x80)
		{
			spaceship2->rotation += 0.25f;
		}

		if (DirectInputManager::diKeys[DIK_DOWN] & 0x80)
		{
			spaceship2->vel.x = 0;
			spaceship2->vel.y = 0;

			spaceship2->accel.x = 0;
			spaceship2->accel.y = 0;

			spaceship2->engineForce.x = 0;
			spaceship2->engineForce.y = 0;
		}

		if (DirectInputManager::diKeys[DIK_B] & 0x80) 
		{
			Game* currentGame = Game::gameStack.back();

			currentGame->CleanUp();
			Game::gameStack.pop_back();

			delete currentGame;
			currentGame = nullptr;

			AudioManager::PlayMainMenuSound();

			return;
		}

		if (circleCollisionDetection(spaceship1->spriteWidth / 2, spaceship2->spriteWidth / 2, spaceship1->pos + spaceship1->spriteCenter, spaceship2->pos + spaceship2->spriteCenter))
		{
			// Find the centre positions of both spaceships
			D3DXVECTOR2 center1 = spaceship1->pos + spaceship1->spriteCenter;
			D3DXVECTOR2 center2 = spaceship2->pos + spaceship2->spriteCenter;
			
			// Find collision normal
			D3DXVECTOR2 colNormal = center2 - center1;

			float distance = D3DXVec2Length(&colNormal);

			if (distance > 0.0f)
			{
				D3DXVec2Normalize(&colNormal, &colNormal);
				
				float radius1 = spaceship1->spriteWidth / 2.0f;
				float radius2 = spaceship2->spriteWidth / 2.0f;

				float overlap = (radius1 + radius2) - distance;

				if (overlap > 0.0f)
				{
					spaceship1->pos -= colNormal * (overlap / 2.0f);
					spaceship2->pos += colNormal * (overlap / 2.0f);
				}

				// Relative velocity
				D3DXVECTOR2 relativeVelocity = spaceship1->vel - spaceship2->vel;

				// Velocity along collision normal
				float velocityAlongNormal =	D3DXVec2Dot(&relativeVelocity, &colNormal);

				// Only respond if spaceships are moving towards each other
				if (velocityAlongNormal > 0)
				{
					float mass1 = spaceship1->mass;
					float mass2 = spaceship2->mass;

					float impulse = (2.0f * velocityAlongNormal) / (mass1 + mass2);

					spaceship1->vel -= impulse * mass2 * colNormal;
					spaceship2->vel += impulse * mass1 * colNormal;
				}
			}

			cout << "collided" << endl;
		}

		spaceship1->vel += spaceship1->accel;
		spaceship2->vel += spaceship2->accel;

		spaceship1->pos += spaceship1->vel;
		spaceship2->pos += spaceship2->vel;

		// Spaceship 1 boundary
		// Top boundary
		if (spaceship1->pos.y < 0)
		{
			spaceship1->pos.y = 0;
			spaceship1->vel.y *= -1;
		}

		// Bottom boundary
		if (spaceship1->pos.y > WindowManager::ScreenHeight - spaceship1->spriteHeight)
		{
			spaceship1->pos.y = WindowManager::ScreenHeight - spaceship1->spriteHeight;

			spaceship1->vel.y *= -1;
		}

		// Left boundary
		if (spaceship1->pos.x < 0)
		{
			spaceship1->pos.x = 0;
			spaceship1->vel.x *= -1;
		}

		// Right boundary
		if (spaceship1->pos.x > WindowManager::ScreenWidth - spaceship1->spriteWidth)
		{
			spaceship1->pos.x = WindowManager::ScreenWidth - spaceship1->spriteWidth;

			spaceship1->vel.x *= -1;
		}

		// Spaceship 2 boundary
		// Top boundary
		if (spaceship2->pos.y < 0)
		{
			spaceship2->pos.y = 0;
			spaceship2->vel.y *= -1;
		}

		// Bottom boundary
		if (spaceship2->pos.y > WindowManager::ScreenHeight - spaceship2->spriteHeight)
		{
			spaceship2->pos.y = WindowManager::ScreenHeight - spaceship2->spriteHeight;

			spaceship2->vel.y *= -1;
		}

		// Left boundary
		if (spaceship2->pos.x < 0)
		{
			spaceship2->pos.x = 0;
			spaceship2->vel.x *= -1;
		}

		// Right boundary
		if (spaceship2->pos.x > WindowManager::ScreenWidth - spaceship2->spriteWidth)
		{
			spaceship2->pos.x = WindowManager::ScreenWidth - spaceship2->spriteWidth;

			spaceship2->vel.x *= -1;
		}
	}
}

void Level2::Render()
{
	DirectXManager::myVirtualGPU->Clear(
		0,
		NULL,
		D3DCLEAR_TARGET,
		D3DCOLOR_XRGB(0, 0, 0),
		1.0f,
		0
	);

	DirectXManager::myVirtualGPU->BeginScene();

	DirectXManager::spriteBrush->Begin(
		D3DXSPRITE_ALPHABLEND
	);


	for (GameObject* object : gameObject)
	{
		D3DXMatrixTransformation2D(
			&object->mat,
			NULL,
			0.0f,
			&object->scaling,
			&object->spriteCenter,
			object->rotation,
			&object->pos
		);

		DirectXManager::spriteBrush->SetTransform(
			&object->mat
		);

		DirectXManager::spriteBrush->Draw(
			object->texture,
			&object->animRect,
			NULL,
			NULL,
			D3DCOLOR_XRGB(255, 255, 255)
		);
	}

	DirectXManager::spriteBrush->End();



	float spaceship1Speed =
		D3DXVec2Length(&spaceship1->vel);

	stringstream ship1Info;

	ship1Info
		<< fixed
		<< setprecision(2);

	ship1Info
		<< "Spaceship 1\n"
		<< "Mass: "
		<< spaceship1->mass
		<< "\n"
		<< "Velocity: "
		<< spaceship1Speed;

	RECT ship1TextRect;

	ship1TextRect.left = 50;
	ship1TextRect.top = 50;
	ship1TextRect.right = 700;
	ship1TextRect.bottom = 250;

	DirectXManager::font->DrawTextA(
		NULL,
		ship1Info.str().c_str(),
		-1,
		&ship1TextRect,
		DT_LEFT,
		D3DCOLOR_XRGB(
			255,
			255,
			255
		)
	);


	float spaceship2Speed =
		D3DXVec2Length(&spaceship2->vel);

	stringstream ship2Info;

	ship2Info
		<< fixed
		<< setprecision(2);

	ship2Info
		<< "Spaceship 2\n"
		<< "Mass: "
		<< spaceship2->mass
		<< "\n"
		<< "Velocity: "
		<< spaceship2Speed;

	RECT ship2TextRect;

	ship2TextRect.left = 1200;
	ship2TextRect.top = 50;
	ship2TextRect.right = 1870;
	ship2TextRect.bottom = 250;

	DirectXManager::font->DrawTextA(
		NULL,
		ship2Info.str().c_str(),
		-1,
		&ship2TextRect,
		DT_LEFT,
		D3DCOLOR_XRGB(
			255,
			255,
			255
		)
	);


	DirectXManager::myVirtualGPU->EndScene();

	DirectXManager::myVirtualGPU->Present(
		NULL,
		NULL,
		NULL,
		NULL
	);
}

void Level2::CleanUp()
{
	for (GameObject* obj : gameObject)
	{
		if (obj != nullptr)
		{
			if (obj->texture != nullptr)
			{
				obj->texture->Release();
				obj->texture = nullptr;
			}

			delete obj;
		}
	}

	gameObject.clear();

	bg = nullptr;
	spaceship1 = nullptr;
	spaceship2 = nullptr;
}

Level2::Level2()
{}