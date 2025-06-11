#include <iostream>
#include "raylib.h"
#include "resource_dir.h"
#include "raymath.h"
using namespace std;


class MeshInstance
{
public:
    Vector3 position;
    Vector3 rotation;

    Material material;
    Mesh mesh;

    BoundingBox collider;
    Matrix matrix;

    bool debug = true;

    MeshInstance()
    {
        this->position = (Vector3){0, 0, 0};
        this->rotation = (Vector3){0, 0, 0};

        this->material = LoadMaterialDefault();
        mesh = GenMeshCube(1.0f, 1.0f, 1.0f);
        collider = GetMeshBoundingBox(mesh);
    }

    MeshInstance(Vector3 position, Vector3 rotation, Vector3 dimentions, Material material) // box
    {
        this->position = position;
        this->rotation = rotation;
        this->material = material;
        mesh = GenMeshCube(dimentions.x, dimentions.y, dimentions.z);
        collider = GetMeshBoundingBox(mesh);
    }

    void draw()
    {
        matrix = MatrixMultiply(MatrixRotate(rotation, 1), MatrixTranslate(position.x, position.y, position.z)); // rotation DOES NOT WORK!
        DrawMesh(mesh, material, matrix);
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
        BoundingBox transformedBox = {newMin, newMax};

        if (debug)
        {
            DrawBoundingBox(transformedBox, RED);
        }
    }
};