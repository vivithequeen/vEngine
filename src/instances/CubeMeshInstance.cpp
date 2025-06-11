#include <iostream>
#include <string>
#include "raylib.h"
#include "resource_dir.h"
#include "raymath.h"
#include <cstring>
#include "MeshInstance.cpp"

class CubeMeshInstance: public MeshInstance
{   
    private:
    Vector3 dimentions;
    public:

    CubeMeshInstance(Vector3 pos, Vector3 rot, Vector3 di, MaterialInstance mes, string id) // box
    {
        this->position = pos;
        this->rotation = rot;
        this->material = mes;
        this-> dimentions = di;
        this->id = id;

        updateMesh();
    }

    int updateMesh(){
        mesh = GenMeshCube(dimentions.x, dimentions.y, dimentions.z);
        collider = GetMeshBoundingBox(mesh);
        return 0;
    }
};