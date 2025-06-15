#include <iostream>
#include <vector>
#include <cstdint>
#include "raylib.h"
#include "rcamera.h"
#include "resource_dir.h"
#include "raymath.h"
#include "imgui.h"
#include "rlImGui.h"
#include "../instances/Instance.cpp"


class EditorInstanceWindow
{

    public:
    Instance* instance;
    bool open;
    EditorInstanceWindow(){
        open = false;
    };
    EditorInstanceWindow(Instance* i){
        instance = i;
        open = true;
    };


    bool showWindow(){
        ImGui::Begin(instance->getNameAsChar(), &open, ImGuiWindowFlags_MenuBar); // add name functionality
        instance->getEditorOptions();//CHANGE SEPERATE INSTANCE MANAGERS TO JUST BE A SINGLE INSTANGE MANAGER
        ImGui::End();

        return open;
    }
};