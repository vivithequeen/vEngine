#include <iostream>
#include <vector>
#include <cstdint>
#include "raylib.h"
#include "rcamera.h"
#include "resource_dir.h"
#include "raymath.h"
#include "imgui.h"
#include "rlImGui.h"

class EditorConsole
{   
    /*
    easy to use log
    timestamps
    major errors and minor errors
    take over the program crashing?



    */


    public:
    bool editorConsoleOpen;

    EditorConsole(){
        editorConsoleOpen = true;
    }

    int drawConsole(){
        if(editorConsoleOpen)
        {
            ImGui::Begin("Console", &editorConsoleOpen,ImGuiWindowFlags_MenuBar);

            ImGui::End();
        }
        return 0;
    }


};