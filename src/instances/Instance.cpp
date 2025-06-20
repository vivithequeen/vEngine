#include <iostream>
#include "raylib.h"
#include "resource_dir.h"
#include "raymath.h"
#include "imgui.h"
#include "rlImGui.h"
#include "../editor/EditorCamera.cpp"
#include <string>
using namespace std;
#ifndef INSTANCE
#define INSTANCE
class Instance
{
    public:
    string name;

    string type;
    Instance()
    {
        name = "no name";
    }
    const char* getNameAsChar() {
        return name.c_str();
    }

    virtual int process(EditorCamera editorCamera)
    {
        return 0;
    }


    virtual int getEditorOptions(){
        ImGui::SeparatorText("Instance");
        //static char placeHolder[128] = "Type Here"; //sections for ObjectInstance then MeshInstance ect
        static char nameBuffer[128];
        strncpy(nameBuffer, name.c_str(), sizeof(nameBuffer));
        nameBuffer[sizeof(nameBuffer) - 1] = '\0';
        if (ImGui::InputText("Name", nameBuffer, sizeof(nameBuffer))) {
            name = nameBuffer;
        }
        return 0;
    }
    virtual string getSaveString()
    {
        string str;
        str+="Instance:Name:" + name+"bsinst";
        return str;
        
    }
    virtual ~Instance() = default;
    
};
#endif