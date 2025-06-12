
#include <iostream>
#include <vector>

#include "raylib.h"
#include "resource_dir.h"

#include "../instances/MeshInstance.cpp"
#include "../instances/CubeMeshInstance.cpp"
#include "../instances/PlaneMeshInstance.cpp"
using namespace std;

class MeshInstanceManager
{
private:
	vector<MeshInstance> meshs = {};
	int currentid;
public:
	MeshInstanceManager()
	{
	}

	int addMesh(MeshInstance meshInstance)
	{
		meshs.push_back(meshInstance);
		return 0;
	}

	MeshInstance getMaterialByIndex(int index)
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
		addMesh(m);
		return 0;
	}
	int makePlaneMesh(Vector3 pos, Vector3 rot, Vector2 di, MaterialInstance mes){
		PlaneMeshInstance m(pos, rot, di, mes, makeId("planemesh"));
		addMesh(m);
		return 0;
	}
	
	int drawMesh()
	{
		// meshs[0].draw();
		for (MeshInstance mesh : meshs)
		{
			mesh.draw();
		}

		return 0;
	}
	int process()
	{

		drawMesh();
		return 0;
	}
};