#include <iostream>
#include "raylib.h"
#include "resource_dir.h"
#include "raymath.h"
#include "Instance.cpp"
#include "MaterialInstance.cpp"
#include "TransformInstance.cpp"
#include "ColliderInstance.cpp"

using namespace std;
#ifndef MODEL_INSTANCE
#define MODEL_INSTANCE
class ModelInstance : public TransformInstance
{
    public:
    Model model;
    ColliderInstance colliderInstance;
    MaterialInstance material;
    string filepath;
    ModelInstance(Vector3 pos, Vector3 rot){
        this->position = pos;
        this->rotation = rot;
        this->material = MaterialInstance();


        this->name = "ModelInstance";
        this->type = "ModelInstance";
        model = LoadModelFromMesh(GenMeshCube(1,1,1));
        model.materials[0]=material.getMaterial();
        //model = LoadModel("bomb.glb");
    }
    BoundingBox getTransformedBox()
    {
        matrix = MatrixMultiply(MatrixRotateXYZ(rotation), MatrixTranslate(position.x, position.y, position.z)); 

        Vector3 corners[8] = {
            {colliderInstance.collider.min.x, colliderInstance.collider.min.y, colliderInstance.collider.min.z},
            {colliderInstance.collider.min.x, colliderInstance.collider.min.y, colliderInstance.collider.max.z},
            {colliderInstance.collider.min.x, colliderInstance.collider.max.y, colliderInstance.collider.min.z},
            {colliderInstance.collider.min.x, colliderInstance.collider.max.y, colliderInstance.collider.max.z},
            {colliderInstance.collider.max.x, colliderInstance.collider.min.y, colliderInstance.collider.min.z},
            {colliderInstance.collider.max.x, colliderInstance.collider.min.y, colliderInstance.collider.max.z},
            {colliderInstance.collider.max.x, colliderInstance.collider.max.y, colliderInstance.collider.min.z},
            {colliderInstance.collider.max.x, colliderInstance.collider.max.y, colliderInstance.collider.max.z}};

        // Transform all corners
        for (int i = 0; i < 8; i++)
        {
            corners[i] = Vector3Transform(corners[i], matrix);
        }

        // Find new min and max
        Vector3 newMin = corners[0];
        Vector3 newMax = corners[0];
        for (int i = 1; i < 8; i++)
        {
            newMin = Vector3Min(newMin, corners[i]);
            newMax = Vector3Max(newMax, corners[i]);
        }
        return (BoundingBox){newMin, newMax};
    }
    int process(EditorCamera editorCamera) override
    {
        BoundingBox transformedBox = getTransformedBox();
        //model.transform = matrix;
        DrawModel(model,Vector3Zero(),1.0f,WHITE);
        return 0;
    }
    int getEditorOptions() override
    {
        TransformInstance::getEditorOptions();
        ImGui::SeparatorText("ModelInstance");
        
        
        if(ImGui::TreeNode("ColliderInstance"))
        {
            colliderInstance.getEditorOptions();
            ImGui::TreePop();
        }
        if(ImGui::TreeNode("MaterialInstance"))
        {
            material.getEditorOptions();
            ImGui::TreePop();
        }

        ImGui::Text("Model Filepath: %s", filepath.c_str());
        ImGui::Button("Upload Model");
        if(ImGui::BeginDragDropTarget()){
            if(const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("FILEPATH")){
                std::string newFilePath((const char*)payload->Data, payload->DataSize - 1); 
                newFilePath = newFilePath.substr(13);
                if(newFilePath.substr(newFilePath.size()-3,newFilePath.size()) == "glb")
                {
                    filepath = newFilePath;
                    model = LoadModel(filepath.c_str());
                    model.materials[0]=material.getMaterial();
                }
            }
        }
        return 0;
    }
};
#endif