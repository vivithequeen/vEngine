#include <iostream>
#include "raylib.h"
#include "resource_dir.h"
#include "raymath.h"
#include "MaterialInstance.cpp"
using namespace std;

class MeshInstance
{
private:
    Vector3 position;
    Vector3 rotation;

    MaterialInstance material;
    Mesh mesh;

    BoundingBox collider;
    Matrix matrix;

    string id;
    bool debug = true;

public:
    MeshInstance()
    {
        this->position = (Vector3){0, 0, 0};
        this->rotation = (Vector3){0, 0, 0};

        this->material = MaterialInstance();
        mesh = GenMeshCube(1.0f, 1.0f, 1.0f);
        collider = GetMeshBoundingBox(mesh);
    }

    MeshInstance(Vector3 pos, Vector3 rot, Vector3 di, MaterialInstance mes, string id) // box
    {
        this->position = pos;
        this->rotation = rot;
        this->material = mes;
        this->id = id;
        mesh = GenMeshCube(di.x, di.y, di.z);
        collider = GetMeshBoundingBox(mesh);
    }
    MeshInstance(Vector3 pos, Vector3 rot, Vector2 di, MaterialInstance mes, string id) // plane
    {
        this->position = pos;
        this->rotation = rot;
        this->material = mes;
        this->id = id;
        mesh = GenMeshPlane(di.x, di.y, 1, 1);
        collider = GetMeshBoundingBox(mesh);
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