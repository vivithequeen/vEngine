#include <iostream>
#include <vector>
#include <cstdint>
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


    int draw2D(RenderTexture2D renderTexture){

        rlImGuiBegin();

        bool my_tool_active = true;
        bool *b = &my_tool_active;
        ImTextureID texture = (ImTextureID)(uintptr_t)renderTexture.texture.id;
   
        ImGuiIO& io = ImGui::GetIO();
        ImFont* myFont = io.Fonts->Fonts[1];
        ImGui::PushFont(myFont);

        ImGui::Begin("Editor Config", b, ImGuiWindowFlags_MenuBar);

        ImGui::PopFont();
        ImGui::End();
        ImGui::Begin("3d Window", b, ImGuiWindowFlags_MenuBar);
        ImGui::Image(texture, ImGui::GetWindowSize(),ImVec2(0,1),ImVec2(1,0));
        ImGui::PopFont();
        ImGui::End();
        
        


        rlImGuiEnd();
        return 0;
    }
};