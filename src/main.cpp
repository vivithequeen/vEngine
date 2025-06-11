#include <iostream>
#include <vector>
#include "raylib.h"
#include "rcamera.h"
#include "resource_dir.h"	
#include "raymath.h"

#include "handlers/InstanceManager.cpp"
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




	Player player;
	HideCursor();
	DisableCursor();
	// game loop

	InstanceManager instanceHandler;

	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{

		// drawing
		player.process(GetFrameTime());
		BeginDrawing();
		ClearBackground(BLACK);
		BeginMode3D(player.camera);
		DrawGrid(17,1);
		instanceHandler.process();

		EndMode3D();
		DrawFPS(0,0);
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
