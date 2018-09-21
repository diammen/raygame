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
	int multiplier = 10;

	Player player = {0,0};
	Rectangle box = { 0,0,32,32 };

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	Image ball = LoadImage("ballshade.png");
	ImageCrop(&ball, box);

	Texture2D texture = LoadTextureFromImage(ball);
	SetTargetFPS(60);
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		// TODO: Update your variables here
		if (IsKeyDown(KEY_A))
		{
			box.x-= 1 * multiplier;
		}
		if (IsKeyDown(KEY_D))
		{
			box.x+= 1 * multiplier;
		}
		if (IsKeyDown(KEY_W))
		{
			box.y -= 1 * multiplier;
		}
		if (IsKeyDown(KEY_S))
		{
			box.y += 1 * multiplier;
		}
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(GRAY);

		DrawTexture(texture, box.x, box.y, WHITE);
		//DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	UnloadTexture(texture); // Texture unloading

	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}