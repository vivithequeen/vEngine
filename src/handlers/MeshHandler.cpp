
#include <iostream>
#include <vector>

#include "raylib.h"
#include "resource_dir.h"

#include "MeshInstance.cpp"
using namespace std;

class MeshHandler
{
	vector<MeshInstance> meshs= {
		MeshInstance((Vector3){0,3,0},(Vector3){0,0,0},(Vector3){1,3,1},test),
	};
};