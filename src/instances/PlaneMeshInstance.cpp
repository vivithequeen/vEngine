#include <iostream>
#include <string>
#include "raylib.h"
#include "resource_dir.h"
#include "raymath.h"
#include <cstring>
#include "MeshInstance.cpp"


class PlaneMeshInstance : public MeshInstance{
    private:
        Vector2 dimentions;
    public:
    PlaneMeshInstance(Vector3 pos, Vector3 rot, Vector2 di, MaterialInstance mes, string id) // plane
    {
        this->position = pos;
        this->rotation = rot;
        this->material = mes;
        this->dimentions = di;
        this->id = id;
        updateMesh();

    }
    int updateMesh(){
        mesh = GenMeshPlane(dimentions.x, dimentions.y, 1, 1);
        collider = GetMeshBoundingBox(mesh);
        return 0;
    }
};