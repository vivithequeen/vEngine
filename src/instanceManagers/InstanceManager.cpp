
#include <iostream>
#include <vector>

#include "raylib.h"
#include "resource_dir.h"
#include "../instances/CubeMeshInstance.cpp"
#include "../instances/PlaneMeshInstance.cpp"


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


        makeCubeMesh((Vector3){0, 2, 0}, (Vector3){0, 0, 0}, (Vector3){3, 3, 3});
        makePlaneMesh((Vector3){0, 0, 0}, (Vector3){0, 0, 0}, (Vector2){2, 2});
    }

    int process(float dt)
    {
        drawMesh();
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
	
	int drawMesh()
	{
		// meshs[0].draw();
		for (auto ins : instances)
		{
			ins->process();
		}

		return 0;
	}


};
#endif