#include <iostream>
#include <string>
#include "raylib.h"
#include "resource_dir.h"
#include "raymath.h"
#include <cstring>
#include "MeshInstance.cpp"
#ifndef CUBE_MESH_INSTANCE
#define CUBE_MESH_INSTANCE
class CubeMeshInstance: public MeshInstance
{   
    private:
    Vector3 dimentions;
    public:

    CubeMeshInstance(Vector3 pos, Vector3 rot, Vector3 di, MaterialInstance mes, string mId) // box
    {
        this->position = pos;
        this->rotation = rot;
        this->material = mes;
        this-> dimentions = di;
        this->id = mId;

        updateMesh();
    }

    int updateMesh(){
        mesh = GenMeshCube(dimentions.x, dimentions.y, dimentions.z);
        colliderInstance.collider = GetMeshBoundingBox(mesh);
        return 0;
    }
    int getEditorOptions() override
    { 
        MeshInstance::getEditorOptions();
        ImGui::SeparatorText("CubeMeshInstance");
        static float dimentionsEditor[3] = { dimentions.x, dimentions.y, dimentions.z};
        
        ImGui::InputFloat3("Dimentions", dimentionsEditor);
        return 0;
    }
};
#endif