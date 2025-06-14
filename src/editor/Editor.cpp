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
private:
    bool mouse_locked;
    
    bool editorSettingsOpen;
    bool gameWindowOpen;
public:
    

    EditorCamera editorCamera;

    Editor()
    {

        mouse_locked = true;
        editorSettingsOpen = true;
        gameWindowOpen = true;

    }

    int process(float dt)
    {
        editorCamera.process(dt);
        return 0;
    }

    int draw2D(RenderTexture2D renderTexture)
    {

        rlImGuiBegin();
        // values

        // graphics stoof
        bool my_tool_active = true;
        bool *b = &my_tool_active;
        ImTextureID texture = (ImTextureID)(uintptr_t)renderTexture.texture.id;

        ImGuiIO &io = ImGui::GetIO();


        ImFont *myFont = io.Fonts->Fonts[1];

        ImGui::PushFont(myFont);
        mainMenuBar();

    
        editorSettingsWindow();
        gameWindow(renderTexture);
        ImGui::PopFont();

        rlImGuiEnd();
        return 0;
    }

    int mainMenuBar(){
        ImGui::BeginMainMenuBar();
        if(ImGui::BeginMenu("File")){
            ImGui::EndMenu();
        }
        if(ImGui::BeginMenu("Edit")){
            ImGui::EndMenu();
        }
        if(ImGui::BeginMenu("Settings")){
            ImGui::EndMenu();
        }
        if(ImGui::BeginMenu("Windows")){

            ImGui::MenuItem("Editor Settings", NULL, &editorSettingsOpen); // errors because it doesnt like me
            ImGui::MenuItem("Game Window", NULL, &gameWindowOpen); // errors because it doesnt like me

            ImGui::EndMenu();
        }
        if(ImGui::BeginMenu("Save")){
            ImGui::EndMenu();
        }
        if(ImGui::BeginMenu("Build")){
            ImGui::EndMenu();
        }
        if(ImGui::BeginMenu("Help")){
            ImGui::EndMenu();
        }

        
        ImGui::EndMainMenuBar();
        return 0;
    }
    int editorSettingsWindow(){
        if(editorSettingsOpen)
        {
            if(ImGui::Begin("Editor Config", &editorSettingsOpen, ImGuiWindowFlags_MenuBar))
            {
                if (ImGui::Checkbox("lock mouse", &mouse_locked))
                {
                
                };
                ImGui::End();
            }

        }
        return 0;
    }
    int gameWindow(RenderTexture2D renderTexture){
        if(gameWindowOpen)
        {
            //does not scale correctly, it should keep its proportions
            ImTextureID texture = (ImTextureID)(uintptr_t)renderTexture.texture.id;

            ImGui::Begin("Game Window", &gameWindowOpen, ImGuiWindowFlags_MenuBar);
            ImGui::Image(texture, ImGui::GetWindowSize(), ImVec2(0, 1), ImVec2(1, 0));

            
            ImGui::End();
        }
        return 0;
    }
};