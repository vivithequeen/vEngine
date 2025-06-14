#include <iostream>
#include "raylib.h"
#include "resource_dir.h"
#include "raymath.h"
#include "MaterialInstance.cpp"
#include "TransformInstance.cpp"
#include "ColliderInstance.cpp"
using namespace std;
#ifndef MESH_INSTANCE
#define MESH_INSTANCE

class MeshInstance : public TransformInstance
{
private:

    

public:
    string id;
    Mesh mesh;
    
    MaterialInstance material;
    ColliderInstance colliderInstance;

    MeshInstance()
    {

    }

    BoundingBox getTransformedBox()
    {
        matrix = MatrixMultiply(MatrixRotate(rotation, 1), MatrixTranslate(position.x, position.y, position.z)); // rotation DOES NOT WORK!

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
    BoundingBox getBoundingBox()
    {
        return getTransformedBox();
    }

    void draw()
    {

        BoundingBox transformedBox = getTransformedBox();
        DrawMesh(mesh, material.getMaterial(), matrix);
        if (colliderInstance.debugVisible)
        {
            DrawBoundingBox(transformedBox, RED);
        }
    }
    int getEditorOptions() override
    {
        TransformInstance::getEditorOptions();
        ImGui::SeparatorText("MeshInstance");
        
        if(ImGui::CollapsingHeader("ColliderInstance"))
        {
            colliderInstance.getEditorOptions();
        }
        if(ImGui::CollapsingHeader("MaterialInstance"))
        {
            
        }        
        return 0;
    }
};
#endif