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
	int multiplier = 5;
	int currentFrame = 0;
	int frameCounter = 0;
	int frameSpeed = 10;

	int slashFrame = 0;
	int slashFrameCounter = 0;

	bool playAnimation = false;

	Player player = {0,0};
	Rectangle box = { 0,0,32,32 };
	Rectangle slashBox = { 0,0,32,32 };

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	Vector2 position = { 100.0f, 100.0f };
	Vector2 slashPosition = { 120.0f, 100.0f };
	Vector2 direction = { 0.0f, 0.0f };

	Texture2D ballTexture = LoadTexture("ballshade5.png");
	Texture2D slashTexture = LoadTexture("slash2.png");

	SetTargetFPS(60);
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		frameCounter++;

		direction = { 0,0 };

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
			position.x -= 1 * multiplier;
			slashPosition.x -= 1 * multiplier;
			box.x = 32 * 14;
		}
		if (IsKeyDown(KEY_D))
		{
			direction.x += 1;
			position.x += 1 * multiplier;
			slashPosition.x += 1 * multiplier;
			box.x = 32 * 13;
		}
		if (IsKeyDown(KEY_W))
		{
			direction.y -= 1;
			position.y -= 1 * multiplier;
			slashPosition.y -= 1 * multiplier;
			box.x = 32 * 15;
		}
		if (IsKeyDown(KEY_S))
		{
			direction.y += 1;
			position.y += 1 * multiplier;
			slashPosition.y += 1 * multiplier;
			box.x = 32 * 16;
		}
		if (IsKeyPressed(KEY_F))
		{
			playAnimation = true;
		}
		if (playAnimation)
		{
			slashFrameCounter++;
			if (slashFrameCounter >= 60 / frameSpeed)
			{
				slashFrameCounter = 0;
				slashFrame++;

				if (slashFrame > 5)
				{
					playAnimation = false;
					slashFrame = 0;
				}
				slashBox.x = (float)slashFrame*(float)slashTexture.width / 5;
			}
		}

		// physics
		if (position.x < 0)
		{
			position.x = 0;
		}
		if (position.x > screenWidth - box.width)
		{
			position.x = screenWidth - box.width;
		}
		if (position.y < 0)
		{
			position.y = 0;
		}
		if (position.y > screenHeight - box.height)
		{
			position.y = screenHeight - box.height;
		}
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(GRAY);

		DrawTextureRec(ballTexture, box, position, WHITE);
		DrawTextureRec(slashTexture, slashBox, slashPosition, WHITE);

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	UnloadTexture(ballTexture); // Texture unloading

	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}