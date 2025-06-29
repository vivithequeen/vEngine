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
    PlaneMeshInstance(){
        this->position = (Vector3){0,0,0};
        this->rotation = (Vector3){0,0,0};

        this->dimentions = (Vector2){1,1};

        this->name = "PlaneMeshInstance";
        this->type = "PlaneMeshInstance";
        dimentionsEditor[0] = dimentions.x;
        dimentionsEditor[1] = dimentions.y;
        positionEditor[0] = position.x;
        positionEditor[1] = position.y;
        positionEditor[2] = position.z;

        rotationEditor[0] = RAD2DEG * rotation.x; 
        rotationEditor[1] = RAD2DEG * rotation.y;    
        rotationEditor[2] = RAD2DEG *  rotation.z;   
        updateMesh();       
    }
    PlaneMeshInstance(Vector3 pos, Vector3 rot, Vector2 di) // plane
    {
        this->position = pos;
        this->rotation = rot;
        
        this->dimentions = di;

        this->name = "PlaneMeshInstance";
        this->type = "PlaneMeshInstance";
        dimentionsEditor[0] = dimentions.x;
        dimentionsEditor[1] = dimentions.y;
        positionEditor[0] = position.x;
        positionEditor[1] = position.y;
        positionEditor[2] = position.z;

        rotationEditor[0] = RAD2DEG * rotation.x; 
        rotationEditor[1] = RAD2DEG * rotation.y;    
        rotationEditor[2] = RAD2DEG *  rotation.z;   
        updateMesh();

    }
    int updateMesh(){
        mesh = GenMeshPlane(dimentions.x, dimentions.y, 1, 1);
        colliderInstance->collider = GetMeshBoundingBox(mesh);
        return 0;
    }
    float dimentionsEditor[2] ;
    int getEditorOptions() override
    {
        MeshInstance::getEditorOptions();
        ImGui::SeparatorText("PlaneMeshInstance");
        
        

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
    string getSaveString() override
    {
        string str;
        
        str+="pPlaneMeshInstance:Dimentions:(" + to_string(dimentions.x) + "," + to_string(dimentions.y)  + ")planemeshinst";
        str+=MeshInstance::getSaveString();
        return str;

    }
};
#endif