
#include <iostream>
#include <vector>

#include "raylib.h"
#include "resource_dir.h"
#include "../instances/CubeMeshInstance.cpp"
#include "../instances/PlaneMeshInstance.cpp"
#include "../instances/ModelInstance.cpp"
#include "../editor/EditorCamera.cpp"

#ifndef INSTANCE_MANAGER
#define INSTANCE_MANAGER
using namespace std;

class InstanceManager
{

public:
    vector<Instance*> instances;
    //PlayerInstance player;
    InstanceManager()
    {

        // testing!!!!

        instances.push_back(new ModelInstance((Vector3){0, 0, 0},(Vector3){0, 0, 0}));
        //makeCubeMesh((Vector3){0, 2, 0}, (Vector3){0, 0, 0}, (Vector3){3, 3, 3});
        //makePlaneMesh((Vector3){0, 0, 0}, (Vector3){0, 0, 0}, (Vector2){2, 2});
    }

    int process(float dt,EditorCamera editorCamera)
    {
        drawMesh(editorCamera);
        //player.process(dt, meshInstanceManager.getMeshs());
        return 0;
    }
	int makeCubeMesh(Vector3 pos, Vector3 rot, Vector3 di){


		instances.push_back(new CubeMeshInstance(pos,rot,di));
		return 0;
	}
	int makePlaneMesh(Vector3 pos, Vector3 rot, Vector2 di){

		instances.push_back(new PlaneMeshInstance(pos, rot, di));
		return 0;
	}
	
	int drawMesh(EditorCamera editorCamera)
	{
		// meshs[0].draw();
		for (auto ins : instances)
		{
			ins->process(editorCamera);
		}

		return 0;
	}


};
#endif