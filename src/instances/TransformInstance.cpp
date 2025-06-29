#include <iostream>
#include "raylib.h"
#include "resource_dir.h"
#include "raymath.h"
#include "Instance.cpp"
#include "../editor/EditorCamera.cpp"
using namespace std;
#ifndef TRANSFORM_INSTANCE
#define TRANSFORM_INSTANCE
class TransformInstance : public Instance
{

    //(GetRayCollisionBox(GetScreenToWorldRay(GetMousePosition(), editorCamera.camera), transformedBox).hit && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    public:
    Matrix matrix;
    Vector3 position;
    Vector3 rotation;
    bool visible;

    TransformInstance(){
        visible = true;
        matrix = Matrix();

    }
    
    int process(EditorCamera editorCamera) override
    {
        return 0;
    }
    float positionEditor[3]; 
    float rotationEditor[3];
    int getEditorOptions() override
    {
        Instance::getEditorOptions();
        ImGui::SeparatorText("TransformInstance"); 
        


        ImGui::PushID(0);
        if(ImGui::Button("Reset",ImVec2(50,20)))
        {
            positionEditor[0] = 0;
            positionEditor[1] = 0;
            positionEditor[2] = 0;

        }
        ImGui::PopID();
        ImGui::SameLine();
        ImGui::InputFloat3("Position", positionEditor);
        

        position.x = positionEditor[0];
        position.y = positionEditor[1];
        position.z = positionEditor[2];

        ImGui::PushID(1);
        if(ImGui::Button("Reset",ImVec2(50,20)))
        {
            rotationEditor[0] = 0;
            rotationEditor[1] = 0;
            rotationEditor[2] = 0;

        }
        ImGui::PopID();

        ImGui::SameLine();
        ImGui::SliderFloat3("Rotation", rotationEditor,0.0f,360.0f);// figure out steps idk


        rotation.x = rotationEditor[0] * DEG2RAD;
        rotation.y = rotationEditor[1] * DEG2RAD;
        rotation.z = rotationEditor[2] * DEG2RAD;
        ImGui::Checkbox("Visible", &visible); 
        return 0;
    }
    string getSaveString() override
    {
        string str;
        str+="TransformInstance:Position:(" + to_string(position.x) + "," + to_string(position.y) + "," + to_string(position.z) + ")Rotation:("+ to_string(rotation.x) + "," + to_string(rotation.y) + "," + to_string(rotation.z) +")trainst";
        str+=Instance::getSaveString();
        return str;
        
    }
};
#endif
