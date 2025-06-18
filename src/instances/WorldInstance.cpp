#include <iostream>
#include <vector>
#include "raylib.h"
#include "rcamera.h"
#include "resource_dir.h"	
#include "raymath.h"
#include "imgui.h"
#include "rlImGui.h"

#include "../instanceManagers/InstanceManager.cpp"
#include "../instances/PlayerInstance.cpp"
#ifndef WORLD_INSTANCE
#define WORLD_INSTANCE
class WorldInstance
{
    public:

    string worldName;
    InstanceManager* instanceManager;
    EditorCamera editorCamera;

    WorldInstance()
    {
        instanceManager = new InstanceManager;
        worldName = "World Instance";
    }
    WorldInstance(string name)
    { 
        instanceManager = new InstanceManager;
        worldName = name;
    }
    int process(float dt, bool isEditorCameraActive){
        instanceManager->process(dt,editorCamera);
        editorCamera.process(dt, isEditorCameraActive);
        return 0;
    }
};
#endif