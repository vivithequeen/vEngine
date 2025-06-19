#include <iostream>
#include <vector>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <cstdio>
#include "raylib.h"
#include "rcamera.h"
#include "resource_dir.h"
#include "raymath.h"
#include "imgui.h"
#include "rlImGui.h"

#include "../instanceManagers/InstanceManager.cpp"
#include "EditorCamera.cpp"
#include "EditorConsole.cpp"
#include "FileManager.cpp"
#include "../instances/WorldInstance.cpp"

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
    bool newWorldInstanceWindowOpen;
    bool fileLoadWindowOpen;

    bool isEditorCameraActive;

    EditorConsole console;
    Instance *currentInstanceInspectorInstance;
    FileManager fileManager;

    vector<string> filePaths;
    vector<string> lines;
    vector<WorldInstance> worldInstances;
    int currentWorldInstanceIndex;

public:
    Editor()
    {
        ImGuiIO &io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        // ImGui::DockSpaceOverViewport(0,  NULL, ImGuiDockNodeFlags_PassthruCentralNode);
        io.ConfigDockingWithShift = true;
        mouse_locked = true;
        editorSettingsOpen = true;
        gameWindowOpen = true;
        instanceManagerOpen = true;
        newInstanceWindowOpen = false;
        instanceInspectorOpen = true;
        isEditorCameraActive = false;
        assetManagerWindowOpen = true;
        newWorldInstanceWindowOpen = false;
        fileLoadWindowOpen = false;
        currentWorldInstanceIndex = 0;

        console = EditorConsole();

        worldInstances.push_back(WorldInstance());
    }

    int process()
    {
        BeginDrawing();
        draw3D();
        draw2D();
        EndDrawing();
        return 0;
    }
    RenderTexture2D renderTexture = LoadRenderTexture(1920, 1080);
    int draw3D()
    {
        BeginTextureMode(renderTexture);
        ClearBackground(BLACK);

        BeginMode3D(worldInstances.at(currentWorldInstanceIndex).editorCamera.camera);
        DrawGrid(50, 1);
        DrawLine3D((Vector3){-25, 0, 0}, (Vector3){25, 0, 0}, RED);
        DrawLine3D((Vector3){0, -25, 0}, (Vector3){0, 25, 0}, GREEN);
        DrawLine3D((Vector3){0, 0, -25}, (Vector3){0, 0, 25}, BLUE);
        worldInstances.at(currentWorldInstanceIndex).process(GetFrameTime(), isEditorCameraActive);
        EndMode3D();
        DrawFPS(0, 0);
        EndTextureMode();
        return 0;
    }
    int draw2D()
    {

        ClearBackground(BLACK);

        filePaths = getFilePaths("../resources");
        rlImGuiBegin();
        // values
        ImGuiIO &io = ImGui::GetIO();

        ImFont *myFont = io.Fonts->Fonts[1];

        ImGui::PushFont(myFont);
        static bool background = true;
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(float(GetScreenWidth()), float(GetScreenHeight())));
        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoBringToFrontOnFocus |
                                       ImGuiWindowFlags_NoNavFocus |
                                       ImGuiWindowFlags_NoDocking |
                                       ImGuiWindowFlags_NoTitleBar |
                                       ImGuiWindowFlags_NoResize |
                                       ImGuiWindowFlags_NoMove |
                                       ImGuiWindowFlags_NoCollapse |
                                       ImGuiWindowFlags_MenuBar |
                                       ImGuiWindowFlags_NoBackground;
        ImGui::Begin("background", &background, windowFlags);
        ImGui::DockSpace(ImGui::GetID("Dockspace"), ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);
        ImGui::End();
        // graphics stoof
        bool my_tool_active = true;
        bool *b = &my_tool_active;
        ImTextureID texture = (ImTextureID)(uintptr_t)renderTexture.texture.id;

        mainMenuBar();

        editorSettingsWindow();
        gameWindow();
        instanceManagerWindow(worldInstances.at(currentWorldInstanceIndex).instanceManager);
        newInstanceWindow(worldInstances.at(currentWorldInstanceIndex).instanceManager);
        instanceInspectorWindow();
        assetManagerWindow();
        newWorldInstanceWindow();
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
            ImGui::PushID(0);
            ImGui::SeparatorText("Project");
            ImGui::MenuItem("New");
            ImGui::MenuItem("Open");
            if (ImGui::BeginMenu("Recents"))
            {
                ImGui::MenuItem("Bleep bla");
                ImGui::MenuItem("beep beep");
                ImGui::EndMenu();
            }
            ImGui::PopID();

            ImGui::PushID(1);
            ImGui::SeparatorText("World");
            ImGui::MenuItem("New");
            ImGui::MenuItem("Open");
            ImGui::PopID();
            ImGui::PushID(2);
            ImGui::SeparatorText("Instance");
            ImGui::MenuItem("New");
            ImGui::MenuItem("Open");
            ImGui::PopID();
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
            ImGui::MenuItem("Instance Inspector", NULL, &instanceInspectorOpen);
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
        if (ImGui::BeginMenu("About"))
        {

            ImGui::TextLinkOpenURL("Code", "https://github.com/vivithequeen/vEngine");
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

                const char *themes[3] = {"Dark", "Light", "Purple"};
                static int currentItem = 0;

                if (ImGui::Combo("Themes", &currentItem, themes, IM_ARRAYSIZE(themes)))
                {
                    switch (currentItem)
                    {
                    case 0:
                        ImGui::StyleColorsDark();
                        break;
                    case 1:
                        ImGui::StyleColorsLight();
                        break;
                    case 2:
                        ImGui::StyleColorsClassic();
                        break;
                    }
                }
                ImGui::End();
            }
        }
        return 0;
    }
    int gameWindow()
    {
        if (fileLoadWindowOpen)
        {
            string str = fileLoadWindow("Load World Instance");
            if (str != "")
            {
                worldInstances.push_back(fileManager.loadWorldInstance(str));
                fileLoadWindowOpen = false;
            }
        }
        if (gameWindowOpen)
        {
            // does not scale correctly, it should keep its proportions
            ImTextureID texture = (ImTextureID)(uintptr_t)renderTexture.texture.id;

            ImGui::Begin("Game Window", &gameWindowOpen, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar);

            if (ImGui::BeginMenuBar())
            {
                if (ImGui::BeginMenu("File"))
                {
                    if (ImGui::MenuItem("New World Instance", NULL, &newWorldInstanceWindowOpen))
                    {
                    }
                    if (ImGui::MenuItem("Save World Instance"))
                    {
                        fileManager.saveWorldInstance(&worldInstances.at(currentWorldInstanceIndex));
                    }
                    if (ImGui::MenuItem("Load World Instance"))
                    {
                        fileLoadWindowOpen = true;
                    }
                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar();
            }
            ImGui::BeginTabBar("worlds");
            int index = 0;
            for (WorldInstance w : worldInstances)
            {
                ImGui::PushID(index);
                if (ImGui::BeginTabItem(worldInstances.at(index).worldName.c_str()))
                {
                    currentWorldInstanceIndex = index;
                    ImGui::Image(texture, ImVec2(ImGui::GetWindowSize().x, ImGui::GetWindowSize().x * 9.0 / 16), ImVec2(0, 1), ImVec2(1, 0));
                    ImGui::EndTabItem();
                }
                index++;
                ImGui::PopID();
            }
            ImGui::EndTabBar();
            if (ImGui::IsMouseHoveringRect(ImGui::GetWindowPos(), ImVec2(ImGui::GetWindowSize().x, ImGui::GetWindowSize().x * 9.0 / 16)) && ImGui::IsMouseDown(ImGuiMouseButton_Right))
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

            ImGui::End();
        }
        return 0;
    }

    int newWorldInstanceWindow()
    {
        string newWorldInstanceName = "";
        if (newWorldInstanceWindowOpen)
        {
            ImGui::Begin("New World Instance", &newWorldInstanceWindowOpen);
            static char nameInput[128] = "";
            ImGui::InputText("Name", nameInput, IM_ARRAYSIZE(nameInput));

            if (ImGui::Button("Create"))
            {

                worldInstances.push_back(WorldInstance(std::string(nameInput)));
                newWorldInstanceWindowOpen = false;
                newWorldInstanceName = "";
                strcpy(nameInput, "");
            } 
            ImGui::SameLine();
            if (ImGui::Button("Close"))
            {

                newWorldInstanceWindowOpen = false;
            }
            ImGui::End();
        }
        return 0;
    }
    string fileLoadWindow(string windowName)
    {
        static string selectedFilePath = "";
        if (selectedFilePath=="")
        {

            ImGui::Begin(windowName.c_str(), &fileLoadWindowOpen, ImGuiWindowFlags_MenuBar);
            
            if (ImGui::BeginTable("table1", 1))
            {

                ImGui::TableSetupColumn("File Location");

                ImGui::TableHeadersRow();
                static int selectedFileLoad = -1;
                for (int row = 0; row < filePaths.size(); row++)
                {
                    ImGui::TableNextRow();
                    for (int column = 0; column < 1; column++)
                    {
                        ImGui::TableSetColumnIndex(column);
                        if (filesystem::status(filePaths.at(row)).type() == filesystem::file_type::directory)
                        {
                            if (ImGui::TreeNode(filePaths.at(row).c_str()))
                            {
                                ImGui::TreePop();
                            }
                        }
                        else
                        {
                            ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
                            if (ImGui::MenuItem(filePaths.at(row).substr(13).c_str()))
                            {
                               
                                selectedFilePath = filePaths.at(row).substr(13);
                            }
                            // if()
                            if (ImGui::BeginItemTooltip())
                            {
                                selectedFileLoad = column;
                                if (getFileExtension(filePaths.at(row).c_str()) == "png")
                                {
                                    if (currentToolTipTexturePath == filePaths.at(row))
                                    {
                                    }
                                    else
                                    {
                                        toolTipTexture = LoadTexture(filePaths.at(row).c_str());
                                        currentToolTipTexturePath = filePaths.at(row);
                                    }
                                    rlImGuiImageSize(&toolTipTexture, 50, 50);
                                }
                                ImGui::Text("%s", filePaths.at(row).c_str());
                                ImGui::Text("%dbytes", (int)(filesystem::file_size(filePaths.at(row).c_str())));
                                ImGui::EndTooltip();
                            }
                        }
                    }
                }

                ImGui::EndTable();
            }
            ImGui::End();
        }
        
        if (selectedFilePath != "")
        {

            string tempFilePath = selectedFilePath;
            selectedFilePath = "";
            //selectedFilePath.clear();6
            return tempFilePath;
        }
        
        return "";
    }

    int instanceManagerWindow(InstanceManager *instanceManager)
    {
        if (instanceManagerOpen)
        {

            ImGui::Begin("Instance Manager", &instanceManagerOpen, ImGuiWindowFlags_MenuBar);

            if (ImGui::BeginMenuBar())
            {
                if (ImGui::BeginMenu("New"))
                {
                    ImGui::MenuItem("New Instance", NULL, &newInstanceWindowOpen);

                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar();
            }
            int index = 0;
            for (auto *m : instanceManager->instances)
            {
                ImGui::PushID(index);

                if (ImGui::MenuItem(m->getNameAsChar()))
                {
                    currentInstanceInspectorInstance = nullptr;
                    currentInstanceInspectorInstance = m;
                    instanceInspectorOpen = true;
                }
                ImGui::PopID();
                index++;
            }

            ImGui::End();
        }
        return 0;
    }
    int newInstanceWindow(InstanceManager *instanceManager)
    {
        if (newInstanceWindowOpen)
        {
            ImGui::Begin("New Instance Creator", &newInstanceWindowOpen, ImGuiWindowFlags_MenuBar);

            ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
            if (ImGui::TreeNode("Instance"))
            {
                if (ImGui::TreeNode("TransformInstance"))
                {
                    if (ImGui::TreeNode("MeshInstance"))
                    {
                        if (ImGui::Button("PlaneMeshInstance"))
                        {
                            instanceManager->instances.push_back(new PlaneMeshInstance());
                            newInstanceWindowOpen = false;
                        }
                        if (ImGui::Button("CubeMeshInstance"))
                        {
                            instanceManager->instances.push_back(new CubeMeshInstance());
                            newInstanceWindowOpen = false;
                        }
                        ImGui::TreePop();
                    }
                    if (ImGui::Button("ModelInstance"))
                    {
                        instanceManager->instances.push_back(new ModelInstance());
                        newInstanceWindowOpen = false;
                    }
                    if (ImGui::TreeNode("ColliderInstance"))
                    {
                        if (ImGui::Button("BoxColliderInstance"))
                        {
                        }
                        if (ImGui::Button("SphereColliderInstance"))
                        {
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
            ImGui::Begin("Instance Inspector", &instanceInspectorOpen, ImGuiWindowFlags_MenuBar);
            if (currentInstanceInspectorInstance)
            {
                currentInstanceInspectorInstance->getEditorOptions();
            }
            else
            {
                ImGui::TextUnformatted("No Instance Selected");
            }
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
                        if (filesystem::status(filePaths.at(row)).type() == filesystem::file_type::directory)
                        {
                            if (ImGui::TreeNode(filePaths.at(row).c_str()))
                            {
                                ImGui::TreePop();
                            }
                        }
                        else
                        {
                            ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
                            ImGui::TreeNodeEx(filePaths.at(row).substr(13).c_str(), node_flags);
                            // if()
                            if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
                            {
                                const string &path = filePaths.at(row);
                                ImGui::SetDragDropPayload("FILEPATH", path.c_str(), path.size() + 1);

                                if (getFileExtension(filePaths.at(row).c_str()) == "png") // make work with all supported images
                                {
                                    if (currentToolTipTexturePath == filePaths.at(row))
                                    {
                                    }
                                    else
                                    {
                                        toolTipTexture = LoadTexture(filePaths.at(row).c_str());
                                        currentToolTipTexturePath = filePaths.at(row);
                                    }
                                    rlImGuiImageSize(&toolTipTexture, 50, 50);
                                }
                                ImGui::Text("%s", filePaths.at(row).c_str());
                                ImGui::Text("%dbytes", (int)(filesystem::file_size(filePaths.at(row).c_str())));
                                ImGui::EndDragDropSource();
                            }

                            if (ImGui::BeginItemTooltip())
                            {
                                selected = column;
                                if (getFileExtension(filePaths.at(row).c_str()) == "png")
                                {
                                    if (currentToolTipTexturePath == filePaths.at(row))
                                    {
                                    }
                                    else
                                    {
                                        toolTipTexture = LoadTexture(filePaths.at(row).c_str());
                                        currentToolTipTexturePath = filePaths.at(row);
                                    }
                                    rlImGuiImageSize(&toolTipTexture, 50, 50);
                                }
                                ImGui::Text("%s", filePaths.at(row).c_str());
                                ImGui::Text("%dbytes", (int)(filesystem::file_size(filePaths.at(row).c_str())));
                                ImGui::EndTooltip();
                            }
                            // if (column == 1) // size
                            //{
                            //     char buf[256];
                            //     sprintf(buf, "%dbytes", (int)(filesystem::file_size(filePaths.at(row).c_str())));//make so shows thigns correctly (mb, gb ect)
                            //     ImGui::TextUnformatted(buf);
                            // }
                        }
                    }
                }

                ImGui::EndTable();
            }

            ImGui::End();
        }
        return 0;
    }
    vector<string> getFilePaths(const string &directoryPath)
    {
        vector<string> fp;
        for (const auto &entry : filesystem::directory_iterator(directoryPath))
        {
            if (filesystem::is_regular_file(entry) || filesystem::status(entry).type() == filesystem::file_type::directory)
            {
                fp.push_back(entry.path().string());
            }
        }
        return fp;
    }

    string getFileExtension(const string &filepath)
    {
        size_t dotPos = filepath.find_last_of('.');
        if (dotPos != string::npos && dotPos + 1 < filepath.length())
            return filepath.substr(dotPos + 1);
        return "";
    }
};