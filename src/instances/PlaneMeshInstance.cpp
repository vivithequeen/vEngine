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
    PlaneMeshInstance(Vector3 pos, Vector3 rot, Vector2 di) // plane
    {
        this->position = pos;
        this->rotation = rot;
        this->material = MaterialInstance();
        this->dimentions = di;

        this->name = "PlaneMeshInstance";
        this->type = "PlaneMeshInstance";
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
        

        if(ImGui::Button("Reset",ImVec2(50,20)))
        {
            dimentionsEditor[0] = 1;
            dimentionsEditor[1] = 1;
        }


        ImGui::SameLine();
        ImGui::InputFloat2("Dimentions", dimentionsEditor);
        if(dimentions.x != dimentionsEditor[0] || dimentions.y != dimentionsEditor[1] ){
            dimentions.x = dimentionsEditor[0];
            dimentions.y = dimentionsEditor[1];

            updateMesh();
        }
        return 0;
    }
};
#endif