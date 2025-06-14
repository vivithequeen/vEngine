#include <iostream>
#include "raylib.h"
#include "resource_dir.h"
#include "raymath.h"
#include "Instance.cpp"

using namespace std;
#ifndef TRANSFORM_INSTANCE
#define TRANSFORM_INSTANCE
class TransformInstance : public Instance
{
    public:
    Matrix matrix;
    Vector3 position;
    Vector3 rotation;
    bool visible;

    TransformInstance(){
        
    }
    int getEditorOptions() override
    {
        Instance::getEditorOptions();
        ImGui::SeparatorText("TransformInstance"); 
        static float positionEditor[3] = { position.x, position.y, position.z};
        static float rotationEditor[3] = {rotation.x, rotation.y, rotation.z};

        
        ImGui::InputFloat3("Position", positionEditor);
        position.x = positionEditor[0];
        position.y = positionEditor[1];
        position.z = positionEditor[2];
        ImGui::InputFloat3("Rotation", rotationEditor);
        ImGui::Checkbox("Visible", &visible); 
        return 0;
    }
};
#endif
