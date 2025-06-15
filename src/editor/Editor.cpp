#include <iostream>
#include <vector>
#include <cstdint>
#include "raylib.h"
#include "rcamera.h"
#include "resource_dir.h"
#include "raymath.h"
#include "imgui.h"
#include "rlImGui.h"
#include "../instanceManagers/InstanceManager.cpp"
#include "EditorCamera.cpp"
#include "EditorInstanceWindow.cpp"
class Editor
{
private:
    bool mouse_locked;

    bool editorSettingsOpen;
    bool gameWindowOpen;
    bool instanceManagerOpen;
    bool newInstanceWindowOpen;

public:
    EditorCamera editorCamera;
    vector<EditorInstanceWindow> editorInstanceWindows = {};
    Editor()
    {

        mouse_locked = true;
        editorSettingsOpen = true;
        gameWindowOpen = true;
        instanceManagerOpen = true;
        newInstanceWindowOpen = false;
    }

    int process(float dt)
    {
        editorCamera.process(dt);
        return 0;
    }

    int draw2D(RenderTexture2D renderTexture, InstanceManager instanceManager)
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
        instanceManagerWindow(instanceManager);
        newInstanceWindow(instanceManager);
        



        for(int i = 0; i < editorInstanceWindows.size();i++){
            if(editorInstanceWindows.at(i).open == false){
                editorInstanceWindows.erase(editorInstanceWindows.begin() + i);
                return 0;
            }
            editorInstanceWindows.at(i).showWindow();
        }
        ImGui::PopFont();
        rlImGuiEnd();
        return 0;
    }

    int mainMenuBar()
    {
        ImGui::BeginMainMenuBar();
        if (ImGui::BeginMenu("File"))
        {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Settings"))
        {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Windows"))
        {

            ImGui::MenuItem("Editor Settings", NULL, &editorSettingsOpen); 
            ImGui::MenuItem("Game Window", NULL, &gameWindowOpen);         
            ImGui::MenuItem("Instance Manager", NULL, &instanceManagerOpen);
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Save"))
        {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Build"))
        {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help"))
        {
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
        return 0;
    }
    int editorSettingsWindow()
    {

        // cosmetic settings
        // size?

        if (editorSettingsOpen)
        {
            if (ImGui::Begin("Editor Config", &editorSettingsOpen, ImGuiWindowFlags_MenuBar))
            {
                if (ImGui::Checkbox("lock mouse", &mouse_locked))
                {
                };
                ImGui::End();
            }
        }
        return 0;
    }
    int gameWindow(RenderTexture2D renderTexture)
    {
        if (gameWindowOpen)
        {
            // does not scale correctly, it should keep its proportions
            ImTextureID texture = (ImTextureID)(uintptr_t)renderTexture.texture.id;

            ImGui::Begin("Game Window", &gameWindowOpen, ImGuiWindowFlags_MenuBar);

            if (ImGui::BeginMenuBar())
            {
                if (ImGui::BeginMenu("File"))
                {
                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar();
            }

            ImGui::Image(texture, ImGui::GetWindowSize(), ImVec2(0, 1), ImVec2(1, 0));

            ImGui::End();
        }
        return 0;
    }
    int instanceManagerWindow(InstanceManager instanceManager)
    {
        if (instanceManagerOpen)
        {

            ImGui::Begin("Instance Manager", &instanceManagerOpen, ImGuiWindowFlags_MenuBar);

            if (ImGui::BeginMenuBar())
            {
                if (ImGui::BeginMenu("File"))
                {
                    bool placeHolder = true;
                    if(ImGui::MenuItem("New Instance")){
                        editorInstanceWindows.push_back(EditorInstanceWindow());
                    } 
                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar();
            }
            if(ImGui::BeginTabBar("Instances")){
                if(ImGui::BeginTabItem("Mesh")){
                    int index;
                    for(MeshInstance* m : instanceManager.meshInstanceManager.meshs){
                        ImGui::PushID(index);
                        if(ImGui::MenuItem(m->getNameAsChar())){
                            editorInstanceWindows.push_back(EditorInstanceWindow(m));
                        }
                        ImGui::PopID();
                        index++;
                    }
                    
                    ImGui::EndTabItem();
                }
                if(ImGui::BeginTabItem("Models")){
                    ImGui::EndTabItem();
                }
                if(ImGui::BeginTabItem("Materials")){
                    ImGui::EndTabItem();
                }


                ImGui::EndTabBar();
            }

            ImGui::End();
        }
        return 0;
    }
    int newInstanceWindow(InstanceManager instanceManager){
        if(newInstanceWindowOpen){
            ImGui::Begin("New Instance Creator", &newInstanceWindowOpen, ImGuiWindowFlags_MenuBar);
            ImGui::SeparatorText("VisualInstance"); // xyz rotation positon?
            if(ImGui::TreeNode("TransformInstance")){
                if(ImGui::TreeNode("MeshInstance")){
                    if(ImGui::TreeNode("PlaneMeshInstance")){
                    
                        ImGui::TreePop();
                    }
                    if(ImGui::TreeNode("CubeMeshInstance")){
                    
                        ImGui::TreePop();
                    }
                    ImGui::TreePop();
                }
                if(ImGui::TreeNode("ColliderInstance")){
                    if(ImGui::TreeNode("BoxColliderInstance")){
                    
                        ImGui::TreePop();
                    }
                    if(ImGui::TreeNode("SphereColliderInstance")){
                    
                        ImGui::TreePop();
                    }
                    ImGui::TreePop();
                }
                ImGui::TreePop();
            }

            ImGui::End();
        }


        return 0;
    }

};