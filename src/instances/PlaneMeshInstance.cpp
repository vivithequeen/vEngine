#include <iostream>
#include <string>
#include "raylib.h"
#include "resource_dir.h"
#include "raymath.h"
#include <cstring>
#include "MeshInstance.cpp"

#ifndef PLANE_MESH_INSTANCE
#define PLANE_MESH_INSTANCE
class PlaneMeshInstance : public MeshInstance{
    private:
        Vector2 dimentions;
    public:
    PlaneMeshInstance(Vector3 pos, Vector3 rot, Vector2 di, MaterialInstance mes, string mId) // plane
    {
        this->position = pos;
        this->rotation = rot;
        this->material = mes;
        this->dimentions = di;
        this->id = mId;
        updateMesh();

    }
    int updateMesh(){
        mesh = GenMeshPlane(dimentions.x, dimentions.y, 1, 1);
        colliderInstance.collider = GetMeshBoundingBox(mesh);
        return 0;
    }
    int getEditorOptions() override
    {
        MeshInstance::getEditorOptions();
        ImGui::SeparatorText("PlaneMeshInstance");
        static float dimentionsEditor[2] = { dimentions.x, dimentions.y};
        
        ImGui::InputFloat2("Dimentions", dimentionsEditor);
        return 0;
    }
};
#endif