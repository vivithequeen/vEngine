#include <iostream>
#include "raylib.h"
#include "resource_dir.h"
#include "raymath.h"
#include "MaterialInstance.cpp"
using namespace std;
#ifndef MESH_INSTANCE
#define MESH_INSTANCE

class MeshInstance
{
private:


    


    Matrix matrix;

    bool debug = true;

public:
    string id;
    Mesh mesh;
    BoundingBox collider;
    MaterialInstance material;
    Vector3 position;
    Vector3 rotation;

    MeshInstance()
    {

    }

    BoundingBox getTransformedBox()
    {
        matrix = MatrixMultiply(MatrixRotate(rotation, 1), MatrixTranslate(position.x, position.y, position.z)); // rotation DOES NOT WORK!
        DrawMesh(mesh, material.getMaterial(), matrix);
        Vector3 corners[8] = {
            {collider.min.x, collider.min.y, collider.min.z},
            {collider.min.x, collider.min.y, collider.max.z},
            {collider.min.x, collider.max.y, collider.min.z},
            {collider.min.x, collider.max.y, collider.max.z},
            {collider.max.x, collider.min.y, collider.min.z},
            {collider.max.x, collider.min.y, collider.max.z},
            {collider.max.x, collider.max.y, collider.min.z},
            {collider.max.x, collider.max.y, collider.max.z}};

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

        if (debug)
        {
            DrawBoundingBox(transformedBox, RED);
        }
    }
};
#endif