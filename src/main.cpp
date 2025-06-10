#include <iostream>
#include "raylib.h"
#include "resource_dir.h"	
#include "RayCastLogic.cpp"
using namespace std;

int main ()
{
	
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(1920, 1080, "vEngine");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	RayCastLogic rayCastLogic(1,1,90);

	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		// drawing
		BeginDrawing();

		ClearBackground(BLACK);
		char debug[32];
		snprintf(debug, sizeof(debug), "%f", rayCastLogic.getAngle(1920/4) * RAD2DEG);
		DrawText(debug,0,0,18,WHITE);

		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up


	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
