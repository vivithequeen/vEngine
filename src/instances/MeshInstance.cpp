#include <iostream>
#include "raylib.h"
#include "resource_dir.h"
#include "raymath.h"
#include "MaterialInstance.cpp"
#include "TransformInstance.cpp"
#include "ColliderInstance.cpp"
#include "../editor/EditorCamera.cpp"
using namespace std;
#ifndef MESH_INSTANCE
#define MESH_INSTANCE

class MeshInstance : public TransformInstance
{
private:

    

public:

    Mesh mesh;
    
    MaterialInstance *material;
    ColliderInstance *colliderInstance;

    MeshInstance()
    {
        this->material = new MaterialInstance();
        this->colliderInstance = new ColliderInstance();
    }

    BoundingBox getTransformedBox()
    {
        matrix = MatrixMultiply(MatrixRotateXYZ(rotation), MatrixTranslate(position.x, position.y, position.z)); 

        Vector3 corners[8] = {
            {colliderInstance->collider.min.x, colliderInstance->collider.min.y, colliderInstance->collider.min.z},
            {colliderInstance->collider.min.x, colliderInstance->collider.min.y, colliderInstance->collider.max.z},
            {colliderInstance->collider.min.x, colliderInstance->collider.max.y, colliderInstance->collider.min.z},
            {colliderInstance->collider.min.x, colliderInstance->collider.max.y, colliderInstance->collider.max.z},
            {colliderInstance->collider.max.x, colliderInstance->collider.min.y, colliderInstance->collider.min.z},
            {colliderInstance->collider.max.x, colliderInstance->collider.min.y, colliderInstance->collider.max.z},
            {colliderInstance->collider.max.x, colliderInstance->collider.max.y, colliderInstance->collider.min.z},
            {colliderInstance->collider.max.x, colliderInstance->collider.max.y, colliderInstance->collider.max.z}};

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
    BoundingBox getBoundingBox()
    {
        return getTransformedBox();
    }

    int process(EditorCamera editorCamera) override
    {
        Model m;
        
        BoundingBox transformedBox = getTransformedBox();
        if(visible)
        {
            
            DrawMesh(mesh, material->getMaterial(), matrix);

        }
        if (colliderInstance->debugVisible)
        {
            DrawBoundingBox(transformedBox, RED);
        }

        return 0;
    }
    int getEditorOptions() override
    {
        TransformInstance::getEditorOptions();
        ImGui::SeparatorText("MeshInstance");
        
        
        if(ImGui::TreeNode("ColliderInstance"))
        {
            colliderInstance->getEditorOptions();
            ImGui::TreePop();
        }
        if(ImGui::TreeNode("MaterialInstance"))
        {
            material->getEditorOptions();
            ImGui::TreePop();
        }        
        return 0;
    }
    string getSaveString() override
    {
        string str;
        str+="MeshInstance:MaterialInstance:FilePath" + material->getFilePath() + "ColliderInstance:DebugVisible" + to_string(colliderInstance->debugVisible) + "DoesColliton:"+to_string(colliderInstance->doesCollition);
        str+=TransformInstance::getSaveString();
        return str;
    }
};
#endif