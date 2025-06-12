
#include <iostream>
#include <vector>

#include "raylib.h"
#include "resource_dir.h"

#include "MeshInstanceManager.cpp"
#include "MaterialInstanceManager.cpp"
#include "TextureInstanceManager.cpp"
#include "PlayerInstance.cpp"
using namespace std;

class InstanceManager
{

public:
    MeshInstanceManager meshInstanceManager;
    MaterialInstanceManager materialInstanceManager;
    TextureInstanceManager textureInstanceManager;
    PlayerInstance player;
    InstanceManager()
    {

        // testing!!!!
        textureInstanceManager.addTextureFromPath("testMeow.png");
        materialInstanceManager.addMaterial(MaterialInstance(textureInstanceManager.getTextureByIndex(0)));
        meshInstanceManager.makeCubeMesh((Vector3){0, 0, 0}, (Vector3){0, 0, 0}, (Vector3){1, 1, 1}, materialInstanceManager.getMaterialByIndex(0));
        meshInstanceManager.makePlaneMesh((Vector3){0, 0, 0}, (Vector3){0, 0, 0}, (Vector2){2, 2}, materialInstanceManager.getMaterialByIndex(0));
    }

    int process(float dt)
    {
        meshInstanceManager.process();
        player.process(dt);
        return 0;
    }
};