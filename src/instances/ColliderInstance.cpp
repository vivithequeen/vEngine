#include <iostream>
#include "raylib.h"
#include "resource_dir.h"
#include "raymath.h"
#include "MaterialInstance.cpp"
#include "TransformInstance.cpp"
using namespace std;
#ifndef COLLIDER_INSTANCE
#define COLLIDER_INSTANCE
class ColliderInstance : public TransformInstance
{
    public:
    //shape
    bool doesCollition; 
    bool debugVisible; 
    BoundingBox collider;
    ColliderInstance(){
        doesCollition = true; 
        debugVisible = true; 
    }
    int getEditorOptions() override
    {
        TransformInstance::getEditorOptions();
        ImGui::Checkbox("Does Collition", &doesCollition);
        ImGui::Checkbox("Debug Visible", &debugVisible);
        return 0;
    }
};
#endif