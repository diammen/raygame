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
	int frameSpeed = 8;

	int slashFrame = 0;
	int slashFrameCounter = 0;

	Player player = {0,0};
	Rectangle box = { 0,0,32,32 };
	Rectangle slashBox = { 0,0,32,32 };

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	Vector2 position = { 100.0f, 100.0f };
	Vector2 slashPosition = { 150.0f, 100.0f };

	//Image ball1 = LoadImage("ballshade.png");
	//ImageCrop(&ball1, box);
	//box.x = 32;
	//Image ball2 = LoadImage("ballshade.png");
	//ImageCrop(&ball2, box);
	//box.x = 64;
	//Image ball3 = LoadImage("ballshade.png");
	//ImageCrop(&ball3, box);
	//Texture2D texture1 = LoadTextureFromImage(ball1);
	//Texture2D texture2 = LoadTextureFromImage(ball2);
	//Texture2D texture3 = LoadTextureFromImage(ball3);
	Texture2D ballTexture = LoadTexture("ballshade5.png");
	Texture2D slashTexture = LoadTexture("slash.png");

	SetTargetFPS(60);
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		frameCounter++;

		// idle animation
		if (frameCounter >= 60 / frameSpeed)
		{
			frameCounter = 0;
			currentFrame++;

			if (currentFrame > 12) currentFrame = 0;

			box.x = (float)currentFrame*(float)ballTexture.width / 17;
		}
		if (IsKeyDown(KEY_A) && position.x > 0)
		{
			position.x -= 1 * multiplier;
			box.x = 32 * 14;
		}
		if (IsKeyDown(KEY_D) && position.x < screenWidth - 32)
		{
			position.x += 1 * multiplier;
			box.x = 32 * 13;
		}
		if (IsKeyDown(KEY_W) && position.y > 0)
		{
			position.y -= 1 * multiplier;
			box.x = 32 * 15;
		}
		if (IsKeyDown(KEY_S) && position.y < screenHeight - 32)
		{
			position.y += 1 * multiplier;
			box.x = 32 * 16;
		}
		if (IsKeyDown(KEY_F))
		{
			while (slashFrame < 3)
			{
				slashFrameCounter++;
				if (slashFrameCounter >= 60 / frameSpeed)
				{
					slashFrameCounter = 0;
					slashFrame++;

					slashBox.x = (float)slashFrame*(float)slashTexture.width / 3;
				}
			}
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