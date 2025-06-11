
#include <iostream>
#include <vector>

#include "raylib.h"
#include "resource_dir.h"

#include "../instances/MeshInstance.cpp"
using namespace std;

class MeshHandler
{
	private:
	vector<MeshInstance> meshs = {};
	public:
	MeshHandler(){

	}

    int addMesh(MeshInstance meshInstance){
        meshs.push_back(meshInstance);
		return 0;
    }

    MeshInstance getMaterialByIndex(int index){
        return meshs.at(index);
    }
	int drawMesh(){
		//meshs[0].draw();
		for(MeshInstance mesh : meshs){
			mesh.draw();
		}

		return 0;
	}
	int process(){

        drawMesh();
        return 0;
    }
};