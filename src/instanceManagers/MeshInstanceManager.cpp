
#include <iostream>
#include <vector>

#include "raylib.h"
#include "resource_dir.h"

#include "../instances/MeshInstance.cpp"
#include "../instances/CubeMeshInstance.cpp"
#include "../instances/PlaneMeshInstance.cpp"
using namespace std;
#ifndef MESH_INSTANCE_MANAGER
#define MESH_INSTANCE_MANAGER
class MeshInstanceManager
{
private:
	

	int currentid;
public:
	vector<MeshInstance*> meshs = {};
	MeshInstanceManager()
	{
	}

	int addMesh(MeshInstance* meshInstance)
	{
		meshs.push_back(meshInstance);
		return 0;
	}

	MeshInstance* getMeshByIndex(int index)
	{
		return meshs.at(index);
	}

	string makeId(string meshType){
		string str = meshType + to_string(currentid);
		currentid++;
		return str;
	}

	int makeCubeMesh(Vector3 pos, Vector3 rot, Vector3 di, MaterialInstance mes){

		CubeMeshInstance m(pos,rot,di,mes,makeId("cubemesh"));
		addMesh(new CubeMeshInstance(pos,rot,di,mes,makeId("cubemesh")));
		return 0;
	}
	int makePlaneMesh(Vector3 pos, Vector3 rot, Vector2 di, MaterialInstance mes){
		PlaneMeshInstance m(pos, rot, di, mes, makeId("planemesh"));
		addMesh(new PlaneMeshInstance(pos, rot, di, mes, makeId("planemesh")));
		return 0;
	}
	
	int drawMesh()
	{
		// meshs[0].draw();
		for (auto mesh : meshs)
		{
			mesh->process();
		}

		return 0;
	}

	int process()
	{

		drawMesh();
		return 0;
	}
};
#endif