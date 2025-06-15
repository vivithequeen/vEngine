
#include <iostream>
#include <vector>

#include "raylib.h"
#include "resource_dir.h"

#include "MeshInstanceManager.cpp"
#include "MaterialInstanceManager.cpp"



#ifndef INSTANCE_MANAGER
#define INSTANCE_MANAGER
using namespace std;

class InstanceManager
{

public:
    MeshInstanceManager meshInstanceManager;
    MaterialInstanceManager materialInstanceManager;

    //PlayerInstance player;
    InstanceManager()
    {

        // testing!!!!

        materialInstanceManager.addMaterial(MaterialInstance("testMeow.png"));
        meshInstanceManager.makeCubeMesh((Vector3){0, 2, 0}, (Vector3){0, 0, 0}, (Vector3){3, 3, 3}, materialInstanceManager.getMaterialByIndex(0));
        meshInstanceManager.makePlaneMesh((Vector3){0, 0, 0}, (Vector3){0, 0, 0}, (Vector2){2, 2}, materialInstanceManager.getMaterialByIndex(0));
    }

    int process(float dt)
    {
        meshInstanceManager.process();
        //player.process(dt, meshInstanceManager.getMeshs());
        return 0;
    }
};
#endif