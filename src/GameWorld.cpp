#include <iostream>
#include <vector>
#include "raylib.h"
#include "rcamera.h"
#include "resource_dir.h"	
#include "raymath.h"
#include "imgui.h"
#include "rlImGui.h"

#include "instanceManagers/InstanceManager.cpp"
#include "editor/Editor.cpp"
#include "instances/PlayerInstance.cpp"

enum { // mode
    EDIT = 0,
    GAME = 1,
};

class GameWorld
{
    private:
        int gameMode = GAME;
    public:
    	InstanceManager instanceManager;
    	Editor editor;
        PlayerInstance player;
        
    GameWorld()
    {

    }


    Camera getCurrentCamera()
    {
        if(gameMode = EDIT){
            return editor.editorCamera.camera;
        }
        if(gameMode = GAME){
            return player.getCamera();
        }
        return Camera();
    }

    int draw3D(){
        if(gameMode == EDIT)
        {
		    editor.process(GetFrameTime());
        }
        if(gameMode == GAME){
            player.process(GetFrameTime(),instanceManager.meshInstanceManager.getMeshs());
        }
		DrawGrid(17,1);

		instanceManager.process(GetFrameTime());



        return 0;
    }

    int draw2D(){
        DrawFPS(0,0);
        rlImGuiBegin();
        bool my_tool_active = true;
        bool *b = &my_tool_active;
// Create a window called "My First Tool", with a menu bar.
        ImGui::Begin("My First Tool", b, ImGuiWindowFlags_MenuBar);
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
                if (ImGui::MenuItem("Save", "Ctrl+S"))   { /* Do stuff */ }
                if (ImGui::MenuItem("Close", "Ctrl+W"))  { my_tool_active = false; }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }



        // Generate samples and plot them
        float samples[100];
        for (int n = 0; n < 100; n++)
            samples[n] = sinf(n * 0.2f + ImGui::GetTime() * 1.5f);
        ImGui::PlotLines("Samples", samples, 100);

        // Display contents in a scrolling region
        ImGui::TextColored(ImVec4(1,1,0,1), "Important Stuff");
        ImGui::BeginChild("Scrolling");
        for (int n = 0; n < 50; n++)
            ImGui::Text("%04d: Some text", n);
        ImGui::EndChild();

        ImGui::End();
        rlImGuiEnd();

        return 0;
    }

};