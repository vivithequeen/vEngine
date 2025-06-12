
#include <iostream>
#include <vector>

#include "raylib.h"
#include "resource_dir.h"

#include "MeshInstanceManager.cpp"
#include "MaterialInstanceManager.cpp"
#include "TextureInstanceManager.cpp"

using namespace std;

class InstanceManager
{
    private:

    MeshInstanceManager meshInstanceManager;
    MaterialInstanceManager materialInstanceManager;
    TextureInstanceManager textureInstanceManager;
    
    public:
    InstanceManager()
    {
        meshInstanceManager = MeshInstanceManager();
        materialInstanceManager = MaterialInstanceManager();
        textureInstanceManager = TextureInstanceManager();
        //testing!!!!
        textureInstanceManager.addTextureFromPath("testMeow.png");
        materialInstanceManager.addMaterial(MaterialInstance(textureInstanceManager.getTextureByIndex(0)));
        meshInstanceManager.makeCubeMesh((Vector3){0,0,0},(Vector3){0,0,0},(Vector3){1,1,1},materialInstanceManager.getMaterialByIndex(0));
        meshInstanceManager.makePlaneMesh((Vector3){0,0,0},(Vector3){0,0,0},(Vector2){2,2},materialInstanceManager.getMaterialByIndex(0));
    }

    int process(){
        meshInstanceManager.process();
        
        return 0;
    }
};