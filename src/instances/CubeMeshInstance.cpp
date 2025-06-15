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
        this->name = "CubeMeshInstance";
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
        

        if(ImGui::Button("Reset",ImVec2(50,20)))
        {
            dimentionsEditor[0] = 1;
            dimentionsEditor[1] = 1;
            dimentionsEditor[2] = 1;

        }


        ImGui::SameLine();
        ImGui::InputFloat3("Dimentions", dimentionsEditor);

        
        if(dimentions.x != dimentionsEditor[0] || dimentions.y != dimentionsEditor[1] ||dimentions.z != dimentionsEditor[2]){
            dimentions.x = dimentionsEditor[0];
            dimentions.y = dimentionsEditor[1];
            dimentions.z = dimentionsEditor[2];
            updateMesh();
        }



        
        return 0;
    }
};
#endif