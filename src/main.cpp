#include <iostream>
#include <vector>
#include "raylib.h"
#include "rcamera.h"
#include "resource_dir.h"	
#include "raymath.h"
#include "imgui.h"
#include "rlImGui.h"

#include "GameWorld.cpp"

using namespace std;

int main ()
{
	rlImGuiSetup(true);

	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(1920, 1080, "vEngine");
	SetTargetFPS(60);
	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");


	rlImGuiSetup(true);

	//HideCursor();
	//DisableCursor();
	// game loop
 	ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("resources/DMMono-Regular.ttf", 24.0f); // path and size
	GameWorld gameWorld;
	RenderTexture2D renderTexture = LoadRenderTexture(1920, 1080);
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{

		// drawing
		BeginDrawing();
		ClearBackground(BLACK);
		//BeginMode3D(instanceManager.player.getCamera());

		BeginTextureMode(renderTexture);
		ClearBackground(BLACK);
		BeginMode3D(gameWorld.getCurrentCamera());
		gameWorld.draw3D();
		EndMode3D();
		EndTextureMode();

		gameWorld.draw2D(renderTexture);
		
		
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}