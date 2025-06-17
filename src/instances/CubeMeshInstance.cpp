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
    CubeMeshInstance() // box
    {
        this->position = (Vector3){0,0,0};;
        this->rotation = (Vector3){0,0,0};;

        this-> dimentions = (Vector3){1,1,1};;

        this->name = "CubeMeshInstance";
        this->type = "CubeMeshInstance";
        dimentionsEditor[0] = dimentions.x;
        dimentionsEditor[1] = dimentions.y;
        dimentionsEditor[2] = dimentions.z;
        positionEditor[0] = position.x;
        positionEditor[1] = position.y;
        positionEditor[2] = position.z;

        rotationEditor[0] = RAD2DEG * rotation.x; 
        rotationEditor[1] = RAD2DEG * rotation.y;    
        rotationEditor[2] = RAD2DEG *  rotation.z;   
        updateMesh();
    }
    CubeMeshInstance(Vector3 pos, Vector3 rot, Vector3 di) // box
    {
        this->position = pos;
        this->rotation = rot;

        this-> dimentions = di;

        this->name = "CubeMeshInstance";
        this->type = "CubeMeshInstance";
        dimentionsEditor[0] = dimentions.x;
        dimentionsEditor[1] = dimentions.y;
        dimentionsEditor[2] = dimentions.z;
        positionEditor[0] = position.x;
        positionEditor[1] = position.y;
        positionEditor[2] = position.z;

        rotationEditor[0] = RAD2DEG * rotation.x; 
        rotationEditor[1] = RAD2DEG * rotation.y;    
        rotationEditor[2] = RAD2DEG *  rotation.z;   
        updateMesh();
    }

    int updateMesh(){
        mesh = GenMeshCube(dimentions.x, dimentions.y, dimentions.z);
        colliderInstance->collider = GetMeshBoundingBox(mesh);
        return 0;
    }
    float dimentionsEditor[3];
    int getEditorOptions() override
    { 
        MeshInstance::getEditorOptions();
        ImGui::SeparatorText("CubeMeshInstance");
        
        

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
    string getSaveString() override
    {
        string str;
        
        str+="cCubeMeshInstance:Dimentions:(" + to_string(dimentions.x) + "," + to_string(dimentions.y) + "," + to_string(dimentions.z) + ")";
        str+=MeshInstance::getSaveString();
        return str;

    }
};
#endif