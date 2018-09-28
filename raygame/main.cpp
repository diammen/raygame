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
#include "helper.h"

int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 800;
	int screenHeight = 450;
	int multiplier = 2;
	int currentFrame = 0;
	int frameCounter = 0;
	int frameSpeed = 10;
	int playerSpeed = 7;
	int health = 20;
	int timer = 0;
	int counter = 0;
	const int enemySize = 20;
	int enemiesActive = enemySize;

	int slashFrame = 0;
	int slashFrameCounter = 0;

	int explosionFrame = 0;
	int explosionFrameCounter = 0;

	int force = 3;

	bool playAnimation = false;
	bool explosion = false;
	bool gameOver = false;

	Enemy enemy[enemySize];
	Rectangle playerCollision = { -100, -100, 32, 32 };
	Rectangle enemyCollision[20];
	Rectangle box = { 0,0,32,32 };
	Rectangle slashBox = { 0,0,32,32 };
	Rectangle explosionBox{ 0,0,32,32 };
	Rectangle rec = { 0,0,32,32 };


	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	Vector2 position = { 100.0f, 100.0f };
	Vector2 slashPosition = { 120.0f, 100.0f };
	Vector2 explosionPosition = { 0.0f, 0.0f };
	Vector2 direction = { 0.0f, 0.0f };

	Texture2D ballTexture = LoadTexture("ballshade5.png");
	Texture2D slashTexture = LoadTexture("slash2.png");
	Texture2D explosionTexture = LoadTexture("explosion.png");

	// Initialize enemies
	for (int i = 0; i < enemySize; ++i)
	{
		enemy[i].rec.x = 0;
		enemy[i].rec.y = 0;
		enemy[i].rec.width = 32;
		enemy[i].rec.height = 32;
		enemy[i].pos.x = GetRandomValue(screenWidth, screenWidth + 1000);
		enemy[i].pos.y = GetRandomValue(0, screenHeight - enemy[i].rec.height);
		enemy[i].dir = { 0,0 };
		enemy[i].speed = 0;
		enemy[i].active = true;
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


			frameCounter++;
			timer++;

			// timer
			if (timer % 60 == 1)
			{
				counter++;
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
			if (IsKeyPressed(KEY_F))
			{
				playAnimation = true;
			}
			// Play slashing animation
			if (playAnimation)
			{
				playerCollision.x = position.x + 20;
				playerCollision.y = position.y;
				slashFrameCounter++;
				if (slashFrameCounter >= 60 / frameSpeed)
				{
					slashFrameCounter = 0;
					slashFrame++;

					if (slashFrame > 1)
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
			}
			// Play explosion animation
			if (explosion)
			{
				explosionFrameCounter++;
				if (explosionFrameCounter >= 48 / frameSpeed)
				{
					explosionFrameCounter = 0;
					explosionFrame++;

					if (explosionFrame > 6)
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
					enemy[i].pos.x += enemy[i].speed * force;
					enemy[i].speed /= 1.25;
					if (CheckCollisionRecs(playerCollision, enemyCollision[i]))
					{
						explosion = true;
						explosionPosition.x = enemy[i].pos.x;
						explosionPosition.y = enemy[i].pos.y;
						enemy[i].speed = 20;
						//enemy[i].active = false;
						//enemiesKilled++;
					}
				}
			}

			// check win condition
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
			DrawTextureRec(ballTexture, box, position, WHITE);
			if (playAnimation)
			{
				DrawTextureRec(slashTexture, slashBox, slashPosition, WHITE);
			}
			for (int i = 0; i < enemiesActive; ++i)
			{
				if (enemy[i].active)
				{
					DrawTextureRec(ballTexture, enemy[i].rec, enemy[i].pos, WHITE);
				}
			}
			DrawText(FormatText("HEALTH: %i", health), 5, 5, 20, WHITE);
			DrawText(FormatText("TIME: %i", counter), 200, 5, 20, WHITE);
			if (explosion)
			{
				DrawTextureRec(explosionTexture, explosionBox, explosionPosition, WHITE);
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
	UnloadTexture(slashTexture);
	UnloadTexture(explosionTexture);

	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}