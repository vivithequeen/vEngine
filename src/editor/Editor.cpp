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
                    ImGui::MenuItem("New Instance", NULL, &newInstanceWindowOpen); 
                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar();
            }
            if(ImGui::BeginTabBar("Instances")){
                if(ImGui::BeginTabItem("Mesh")){

                    //for each intance

                    //name of instance 
                    //id of instance
                    //texture instance name and id <----
                    //3d x,y,z quards
                    //3d rotation
                    //copy
                    //delete
                    
                    if (ImGui::CollapsingHeader("BoxMesh1")){
                        static char name[128] = "Type Here"; //sections for ObjectInstance then MeshInstance ect
                        ImGui::InputText("Name of Instance", name,128);

                        ImGui::SeparatorText("3D Values"); // placeholder name

                        //ImGui::LabelText("Placeholer id","");
                        static float position[3] = { 0.0f, 0.0f, 0.0f};
                        static float rotation[3] = { 0.0f, 0.0f, 0.0f};

                        ImGui::InputFloat3("Position", position);
                        ImGui::InputFloat3("Rotation", rotation);

                        
                        
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
            if(ImGui::TreeNode("ObjectInstance")){
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