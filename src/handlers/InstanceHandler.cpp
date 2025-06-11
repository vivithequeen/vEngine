
#include <iostream>
#include <vector>

#include "raylib.h"
#include "resource_dir.h"

#include "MeshHandler.cpp"
#include "MaterialHandler.cpp"

using namespace std;

class InstanceHandler
{
    private:
    MeshHandler meshHander;
    MaterialHandler materialHandler;
    public:
    InstanceHandler()
    {
        meshHander = MeshHandler();
        materialHandler = MaterialHandler();

        materialHandler.addMaterial(MaterialInstance("teskMeow.png","test"));
        meshHander.addMesh(MeshInstance((Vector3){1,1,1},(Vector3){0,0,0},(Vector3){1,1,1},materialHandler.getMaterialByIndex(0)));
    }

    int process(){
        meshHander.process();
        
        return 0;
    }
};