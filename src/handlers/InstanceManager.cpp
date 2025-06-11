
#include <iostream>
#include <vector>

#include "raylib.h"
#include "resource_dir.h"

#include "MeshInstanceManager.cpp"
#include "MaterialInstanceManager.cpp"

using namespace std;

class InstanceManager
{
    private:
    MeshInstanceManager meshHander;
    MaterialInstanceManager materialHandler;
    public:
    InstanceManager()
    {
        meshHander = MeshInstanceManager();
        materialHandler = MaterialInstanceManager();

        materialHandler.addMaterial(MaterialInstance("testMeow.png"));
        meshHander.makeCubeMesh((Vector3){0,0,0},(Vector3){0,0,0},(Vector3){1,1,1},materialHandler.getMaterialByIndex(0));
        meshHander.makePlaneMesh((Vector3){0,0,0},(Vector3){0,0,0},(Vector2){2,2},materialHandler.getMaterialByIndex(0));
    }

    int process(){
        meshHander.process();
        
        return 0;
    }
};