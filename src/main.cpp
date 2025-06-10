#include <iostream>
#include "raylib.h"
#include "rcamera.h"
#include "resource_dir.h"	
#include "raymath.h"

#include "Player.cpp"
using namespace std;

int main ()
{
	
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(1920, 1080, "vEngine");
	SetTargetFPS(60);
	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");


	Material test = LoadMaterialDefault();
	Texture texture;
	texture = LoadTexture("testMeow.png");
	SetMaterialTexture(&test, MATERIAL_MAP_DIFFUSE, texture);


	Player player;
	HideCursor();
	DisableCursor();
	// game loop
	Mesh m = GenMeshCube(3,3,3);

	Matrix matrix = MatrixTranslate(0.0f, 3.0f, 0.0f);
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		// drawing
		player.process(GetFrameTime());
		BeginDrawing();
		ClearBackground(BLACK);
		BeginMode3D(player.camera);
		
		DrawPlane((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector2){ 32.0f, 32.0f }, LIGHTGRAY); // Draw ground
        DrawCube((Vector3){ -16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, BLUE);     // Draw a blue wall
        DrawCube((Vector3){ 16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, LIME);      // Draw a green wall
        DrawCube((Vector3){ 0.0f, 2.5f, 16.0f }, 32.0f, 5.0f, 1.0f, GOLD); 		
		
		DrawMesh(m, test, matrix);

		EndMode3D();
		DrawFPS(0,0);
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up

	UnloadMaterial(test);
	UnloadTexture(texture);
	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
