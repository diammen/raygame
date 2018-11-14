/*******************************************************************************************
*
*   raylib [core] example - basic window
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include <time.h>
#include <iostream>
#include <string>
#include <vector>
#include "helper.h"
#include "FallingFactory.h"
using std::vector;

int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 800;
	int screenHeight = 450;
	float multiplier = 1.90f;
	int currentFrame = 0;
	int frameCounter = 0;
	int frameSpeed = 12;
	int bonusSpeed = 12;
	int textSize = 1;
	int textCounter = 0;
	int playerSpeed = 7;
	int health = 100000;
	int timer = 0;
	int counter = 0;
	const int enemySize = 25;
	int enemiesActive = enemySize;
	int enemiesKilled = 0;
	int killCount = 0;

	int slashFrame = 0;
	int slashFrameCounter = 0;
	float slashRotation = 0;

	int explosionFrame = 0;
	int explosionFrameCounter = 0;

	float force = 3;

	bool playAnimation = false;
	bool hit = false;
	bool mileStone = false;
	bool explosion = false;
	bool gameOver = false;

	Enemy enemy[enemySize];
	Rectangle playerCollision = { -100, -100, 32, 32 };
	Rectangle enemyCollision[enemySize];
	Rectangle box = { 0,0,32,32 };
	Rectangle slashBox = { 0,0,32,32 };
	Rectangle explosionBox{ 0,0,32,32 };
	Rectangle rec = { 0,0,32,32 };


	InitWindow(screenWidth, screenHeight, "super game");

	Vector2 position = { 100.0f, 100.0f };
	Vector2 slashPosition = { 120.0f, 100.0f };
	Vector2 explosionPosition = { 0.0f, 0.0f };
	Vector2 direction = { 0.0f, 0.0f };

	Texture2D ballTexture = LoadTexture("ballshade5.png");
	Texture2D spikeBallTexture = LoadTexture("spikeball.png");
	Texture2D slashTexture = LoadTexture("slash2.png");
	Texture2D explosionTexture = LoadTexture("explosion.png");
	Texture2D impactTexture = LoadTexture("explosion1.png");

	vector<Sprite> ents;
	ents.push_back(*FallingFactory::GetInstance().getRandom());

	// Initialize enemies
	for (int i = 0; i < enemySize; ++i)
	{
		enemy[i].rec.x = 0;
		enemy[i].rec.y = 0;
		enemy[i].rec.width = 32;
		enemy[i].rec.height = 32;
		enemy[i].pos.x = GetRandomValue(screenWidth, screenWidth + 1000.0f);
		enemy[i].pos.y = GetRandomValue(0, screenHeight - enemy[i].rec.height);
		enemy[i].dir = { 0,0 };
		enemy[i].speed = 0;
		enemy[i].active = true;
		enemy[i].health = 2;
		enemyCollision[i] = enemy[i].rec;
	}

	SetTargetFPS(60);
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		if (!gameOver)
		{

			for (int i = 0; i < ents.size(); ++i)
			{
				ents[i].translate(Vector2{ 0,200 });
			}
			frameCounter++;
			timer++;

			// timer
			if (timer % 60 == 1)
			{
				counter++;
				ents.push_back(FallingFactory::GetInstance().getRandom()->clone());
			}
				

			direction = { 0,0 };

			// sync collision boxes and move enemies
			for (int i = 0; i < enemySize; ++i)
			{
				enemyCollision[i].x = enemy[i].pos.x;
				enemyCollision[i].y = enemy[i].pos.y;
				enemy[i].pos.x -= 1 * multiplier;
				// if enemy reaches end of screen
				if (enemy[i].pos.x < -32)
				{
					enemy[i].pos.x = GetRandomValue(screenWidth, screenWidth + 1000);
					enemy[i].pos.y = GetRandomValue(0, screenHeight - enemy[i].rec.height);
					enemy[i].health = 2;
					health--;
				}
			
			}

			// idle animation
			if (frameCounter >= 60 / frameSpeed)
			{
				frameCounter = 0;
				currentFrame++;

				if (currentFrame > 12) currentFrame = 0;

				box.x = (float)currentFrame*(float)ballTexture.width / 17;
			}
			if (IsKeyDown(KEY_A))
			{
				direction.x -= 1;
				position.x -= 1 * playerSpeed;
				slashPosition.x = position.x + 20;
				box.x = 32 * 14;
			}
			if (IsKeyDown(KEY_D))
			{
				direction.x += 1;
				position.x += 1 * playerSpeed;
				slashPosition.x = position.x + 20;
				box.x = 32 * 13;
			}
			if (IsKeyDown(KEY_W))
			{
				direction.y -= 1;
				position.y -= 1 * playerSpeed;
				slashPosition.y = position.y;
				box.x = 32 * 15;
			}
			if (IsKeyDown(KEY_S))
			{
				direction.y += 1;
				position.y += 1 * playerSpeed;
				slashPosition.y = position.y;
				box.x = 32 * 16;
			}
			if (IsKeyPressed(KEY_LEFT_SHIFT))
			{
				playerSpeed /= 2;
			}
			if (IsKeyReleased(KEY_LEFT_SHIFT))
			{
				playerSpeed *= 2;
			}
			if (IsKeyPressed(KEY_F))
			{
				playAnimation = true;
			}
			// Play slashing animation
			if (playAnimation)
			{
				if (!hit)
				{
					playerCollision.x = position.x + 20;
					playerCollision.y = position.y;
				}
				else
				{
					playerCollision.x = -100;
					playerCollision.y = -100;
				}
				slashFrameCounter++;
				if (slashFrameCounter >= 60 / frameSpeed - bonusSpeed)
				{
					slashFrameCounter = 0;
					slashFrame++;

					if (slashFrame > 4)
					{
						playAnimation = false;
						slashFrame = 0;
					}
					slashBox.x = (float)slashFrame*(float)slashTexture.width / 5;
				}
			}
			else // Reset collision box to default value
			{
				playerCollision.x = -100;
				playerCollision.y = -100;
				hit = false;
			}
			// Play explosion animation when player hits enemy
			if (explosion)
			{
				explosionFrameCounter++;
				if (explosionFrameCounter >= 48 / frameSpeed)
				{
					explosionFrameCounter = 0;
					explosionFrame++;

					if (explosionFrame > 5)
					{
						explosion = false;
						explosionFrame = 0;
					}
					explosionBox.x = (float)explosionFrame*(float)explosionTexture.width / 7;
				}
			}
			
			// Go through each enemy and check for a collision with the player's attack
			for (int i = 0; i < enemiesActive; ++i)
			{
				if (enemy[i].active)
				{
					//enemy[i].pos.x += enemy[i].speed * force;
					enemy[i].pos.x = AddForce(enemy[i].pos.x, enemy[i].speed, force);
					enemy[i].speed /= 1.25;
					if (CheckCollisionRecs(playerCollision, enemyCollision[i]))
					{
						hit = true;
						explosion = true;
						explosionPosition.x = enemy[i].pos.x;
						explosionPosition.y = enemy[i].pos.y;
						enemy[i].speed = 20;
						enemy[i].health--;
						if (enemy[i].health < 0) enemy[i].health = 0;
						if (enemy[i].health == 0)
						{
							enemy[i].pos.x = GetRandomValue(screenWidth, screenWidth + 1000.0f);;
							enemiesKilled++;
							killCount++;
							if (killCount > 5)
							{
								killCount = 5;
							}
							enemy[i].health = 2;
						}
					}

				}
			}

			if (enemiesKilled % 5 == 0 && enemiesKilled != 0)
			{
				mileStone = true;
			}

			if (mileStone)
			{
				textCounter++;
				if (textCounter < 30)
				{
					textSize += 2;
				}
				else if (textCounter >= 30)
				{
					textSize -= 2;
				}
				if (textCounter >= 55)
				{
					mileStone = false;
					killCount = 0;
					textCounter = 0;
					textSize = 0;
				}
			}

			// check game over condition
			if (health == 0)
			{
				gameOver = true;
			}
			// physics
			if (position.x < 0)
			{
				position.x = 0;
				slashPosition.x = 20;
			}
			if (position.x > screenWidth - box.width)
			{
				position.x = screenWidth - box.width;
				slashPosition.x = screenWidth - box.width;
			}
			if (position.y < 0)
			{
				position.y = 0;
				slashPosition.y = 0;
			}
			if (position.y > screenHeight - box.height)
			{
				position.y = screenHeight - box.height;
				slashPosition.y = screenHeight - box.height;
			}
		}
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(GRAY);
		if (!gameOver)
		{
			for (int i = 0; i < ents.size(); ++i)
			{
				ents[i].draw();
			}
			DrawTextureRec(ballTexture, box, position, WHITE);
			if (playAnimation)
			{
				DrawTexturePro(slashTexture, slashBox, Rectangle{ slashPosition.x, slashPosition.y, 32, 32 }, Vector2{ 0,0 }, 0, WHITE);
			}
			for (int i = 0; i < enemiesActive; ++i)
			{
				if (enemy[i].active)
				{
					//DrawTextureRec(spikeBallTexture, enemy[i].rec, enemy[i].pos, WHITE);
					DrawTextureEx(spikeBallTexture, enemy[i].pos, 0, 1, WHITE);
				}
			}
			DrawText(FormatText("HEALTH: %i", health), 5, 5, 20, WHITE);
			DrawText(FormatText("TIME: %i", counter), 200, 5, 20, WHITE);
			DrawText(FormatText("Kills: %i", enemiesKilled), 400, 5, 20, WHITE);
			if (explosion)
			{
				DrawTextureRec(explosionTexture, explosionBox, explosionPosition, WHITE);
			}
			if (mileStone)
			{
				DrawText("Bonus!", GetScreenWidth() / 2 - MeasureText("Bonus!", textSize) / 2, GetScreenHeight() / 2 - 50, textSize, WHITE);
			}
		}
		else
		{
			DrawText("YOU LOSE", GetScreenWidth() / 2 - MeasureText("YOU LOSE", 20) / 2, GetScreenHeight() / 2 - 50, 20, WHITE);
			DrawText(FormatText("You survived for %i seconds", counter), GetScreenWidth() / 2 - MeasureText("You survived for %i seconds", 20) / 2, GetScreenHeight() / 2 - 100, 20, WHITE);
		}


		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	UnloadTexture(ballTexture); // Texture unloading
	UnloadTexture(spikeBallTexture);
	UnloadTexture(slashTexture);
	UnloadTexture(explosionTexture);
	UnloadTexture(impactTexture);

	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}