#include <iostream>
#include <vector>
#include <cstdint>
#include "raylib.h"
#include "rcamera.h"
#include "resource_dir.h"
#include "raymath.h"
#include "imgui.h"
#include "rlImGui.h"
#include "filesystem"
#include "../instanceManagers/InstanceManager.cpp"
#include "EditorCamera.cpp"
#include "EditorConsole.cpp"

class Editor
{
private:
    bool mouse_locked;

    bool editorSettingsOpen;
    bool gameWindowOpen;
    bool instanceManagerOpen;
    bool newInstanceWindowOpen;
    bool instanceInspectorOpen;
    bool assetManagerWindowOpen;

    bool isEditorCameraActive;

    EditorConsole console;
    Instance *currentInstanceInspectorInstance;

    vector<string> filePaths;

public:
    EditorCamera editorCamera;

    Editor()
    {

        mouse_locked = true;
        editorSettingsOpen = true;
        gameWindowOpen = true;
        instanceManagerOpen = true;
        newInstanceWindowOpen = false;
        instanceInspectorOpen = false;
        isEditorCameraActive = false;
        assetManagerWindowOpen = true;

        console = EditorConsole();
    }

    int process(float dt)
    {
        editorCamera.process(dt, isEditorCameraActive);
        return 0;
    }

    int draw2D(RenderTexture2D renderTexture, InstanceManager instanceManager)
    {
        filePaths = getFilePaths("../resources");
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
        instanceInspectorWindow();
        assetManagerWindow();
        console.drawConsole();

        ImGui::PopFont();
        rlImGuiEnd();
        return 0;
    }

    int mainMenuBar()
    {
        ImGui::BeginMainMenuBar();
        if (ImGui::BeginMenu("File"))
        {
            ImGui::MenuItem("New");
            ImGui::MenuItem("Open");
            if (ImGui::BeginMenu("Recents"))
            {
                ImGui::MenuItem("Bleep bla");
                ImGui::MenuItem("beep beep");
                ImGui::EndMenu();
            }
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
            ImGui::SeparatorText("Editor");
            ImGui::MenuItem("Editor Settings", NULL, &editorSettingsOpen);
            ImGui::MenuItem("Game Window", NULL, &gameWindowOpen);
            ImGui::MenuItem("Instance Manager", NULL, &instanceManagerOpen);
            ImGui::MenuItem("Asset Manager", NULL, &assetManagerWindowOpen);
            ImGui::SeparatorText("Debug");
            ImGui::MenuItem("Console", NULL, &console.editorConsoleOpen);
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
            if (ImGui::IsMouseHoveringRect(ImGui::GetWindowPos(), ImGui::GetWindowSize()) && ImGui::IsMouseDown(ImGuiMouseButton_Right))
            { // freecam mode
                // HideCursor();
                // DisableCursor();
                isEditorCameraActive = true;
            }
            else
            {
                // ShowCursor();
                // EnableCursor();
                isEditorCameraActive = false;
            }

            ImGui::Image(texture, ImVec2(ImGui::GetWindowSize().x, ImGui::GetWindowSize().x * 9.0 / 16), ImVec2(0, 1), ImVec2(1, 0));

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
                    ImGui::MenuItem("New Instance", NULL, &newInstanceWindowOpen);

                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar();
            }
            if (ImGui::BeginTabBar("Instances"))
            {
                if (ImGui::BeginTabItem("Mesh"))
                {
                    int index;
                    for (MeshInstance *m : instanceManager.meshInstanceManager.meshs)
                    { // change to getMeshVector()->vector<MeshInstance>
                        ImGui::PushID(index);
                        if (ImGui::MenuItem(m->getNameAsChar()))
                        {
                            currentInstanceInspectorInstance = m;
                            instanceInspectorOpen = true;
                        }
                        ImGui::PopID();
                        index++;
                    }
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem("Models"))
                {
                    ImGui::EndTabItem();
                }

                ImGui::EndTabBar();
            }

            ImGui::End();
        }
        return 0;
    }
    int newInstanceWindow(InstanceManager instanceManager)
    {
        if (newInstanceWindowOpen)
        {
            ImGui::Begin("New Instance Creator", &newInstanceWindowOpen, ImGuiWindowFlags_MenuBar);
            ImGui::SeparatorText("VisualInstance"); // xyz rotation positon?
            if (ImGui::TreeNode("Instance"))
            {
                if (ImGui::TreeNode("TransformInstance"))
                {
                    if (ImGui::TreeNode("MeshInstance"))
                    {
                        if (ImGui::TreeNode("PlaneMeshInstance"))
                        {

                            ImGui::TreePop();
                        }
                        if (ImGui::TreeNode("CubeMeshInstance"))
                        {

                            ImGui::TreePop();
                        }
                        ImGui::TreePop();
                    }
                    if (ImGui::TreeNode("ColliderInstance"))
                    {
                        if (ImGui::TreeNode("BoxColliderInstance"))
                        {

                            ImGui::TreePop();
                        }
                        if (ImGui::TreeNode("SphereColliderInstance"))
                        {

                            ImGui::TreePop();
                        }
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

    int instanceInspectorWindow()
    {
        if (instanceInspectorOpen)
        {
            ImGui::Begin(currentInstanceInspectorInstance->getNameAsChar(), &instanceInspectorOpen, ImGuiWindowFlags_MenuBar); // add name functionality
            currentInstanceInspectorInstance->getEditorOptions();                                                              // CHANGE SEPERATE INSTANCE MANAGERS TO JUST BE A SINGLE INSTANGE MANAGER
            ImGui::End();
        }
        return 0;
    }

    Texture toolTipTexture;
    string currentToolTipTexturePath;
    int assetManagerWindow()
    {
        if (assetManagerWindowOpen)
        {
            ImGui::Begin("Asset Manager", &assetManagerWindowOpen, ImGuiWindowFlags_MenuBar);
            if (ImGui::BeginTable("table1", 1))
            {
                
                ImGui::TableSetupColumn("File Location");

                ImGui::TableHeadersRow();
                static int selected = -1;
                for (int row = 0; row < filePaths.size(); row++)
                {
                    ImGui::TableNextRow();
                    for (int column = 0; column < 1; column++)
                    {
                        ImGui::TableSetColumnIndex(column);
   
                        char buf[256];
                        snprintf(buf, sizeof(buf), "%s", filePaths.at(row).substr(13).c_str());
                        if(ImGui::Selectable(buf,column)){
                            selected = column;
                        
    
                        }
                        if(ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
                            {
                                const string& path = filePaths.at(row);
                                ImGui::SetDragDropPayload("FILEPATH", path.c_str(), path.size() + 1); // +1 for null terminator
                                
                                ImGui::Text("%s",filePaths.at(row).c_str());
                                if(filePaths.at(row).substr(filePaths.at(row).size()-3,filePaths.at(row).size()) == "png") // make work with all supported images
                                {
                                    if(currentToolTipTexturePath == filePaths.at(row)){

                                    }
                                    else
                                    {
                                        toolTipTexture = LoadTexture(filePaths.at(row).c_str());
                                        currentToolTipTexturePath = filePaths.at(row);
                                    }
                                    rlImGuiImageSize(&toolTipTexture,50,50);

                                }
                                ImGui::EndDragDropSource();
                            }
                        if(ImGui::BeginPopupContextItem()){
                            selected = column;
                            if(filePaths.at(row).substr(filePaths.at(row).size()-3,filePaths.at(row).size()) == "png")
                            {
                                if(currentToolTipTexturePath == filePaths.at(row)){

                                }
                                else
                                {
                                    toolTipTexture = LoadTexture(filePaths.at(row).c_str());
                                    currentToolTipTexturePath = filePaths.at(row);
                                }
                                rlImGuiImageSize(&toolTipTexture,50,50);
                                
                            }
                            ImGui::Text("Full path: %s",filePaths.at(row).c_str());
                            ImGui::Text("File Size: %d",(int)(filesystem::file_size(filePaths.at(row).c_str())));
                            ImGui::EndPopup();
                        }
                        ImGui::SetItemTooltip("Right Click To See Information");
                        //if (column == 1) // size
                        //{
                        //    char buf[256];
                        //    sprintf(buf, "%dbytes", (int)(filesystem::file_size(filePaths.at(row).c_str())));//make so shows thigns correctly (mb, gb ect)
                        //    ImGui::TextUnformatted(buf);
                        //}

                    }
                }
                ImGui::EndTable();
            }

            ImGui::End();
        }
        return 0;
    }
    vector<string> getFilePaths(const std::string &directoryPath)
    {
        vector<string> fp;
        for (const auto &entry : filesystem::directory_iterator(directoryPath))
        {
            if (filesystem::is_regular_file(entry))
            {
                fp.push_back(entry.path().string());
            }
        }
        return fp;
    }
};