#include <iostream>
#include <vector>
#include "raylib.h"
#include "rcamera.h"
#include "resource_dir.h"	
#include "raymath.h"
#include "imgui.h"
#include "rlImGui.h"

#include "EditorCamera.cpp"

class Editor
{
    public:

    EditorCamera editorCamera;

    Editor(){

    }

    int process(float dt){
        editorCamera.process(dt);
        return 0;
    }


    int draw2D(){

        rlImGuiBegin();

        bool my_tool_active = true;
        bool *b = &my_tool_active;

        ImGuiIO& io = ImGui::GetIO();
        ImFont* myFont = io.Fonts->Fonts[1];
        ImGui::PushFont(myFont);

        ImGui::Begin("Editor Config", b, ImGuiWindowFlags_MenuBar);


        
        ImGui::PopFont();
        ImGui::End();
        rlImGuiEnd();
        return 0;
    }
};