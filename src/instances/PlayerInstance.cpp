#include <iostream>
#include <vector>

#include "raylib.h"
#include "rcamera.h"
#include "resource_dir.h"

#include "MeshInstance.cpp"
using namespace std;
#ifndef PLAYER_INSTANCE
#define PLAYER_INSTANCE
class PlayerInstance
{

private:
    Matrix matrix;
    Camera3D camera;
    const float WALKSPEED = 7.0f;

    Vector3 velocity = {0, 0, 0};
    float playerHeight = 2;
    BoundingBox collider;

    Vector3 rotation;

    Mesh playerSize;

    Vector3 playerPosition;
public:
    PlayerInstance()
    {
        camera = {0};
        
        playerPosition = (Vector3){-2.0f, 2.0f, 2.0f};
        camera.position = playerPosition;

        camera.target = (Vector3){0.0f, 2.0f, 0.0f};
        camera.up = (Vector3){0.0f, 1.0f, 0.0f};
        camera.fovy = 60.0f;
        camera.projection = CAMERA_PERSPECTIVE;
        playerSize = GenMeshCube(0.25, 0.5, 0.25);
        collider = GetMeshBoundingBox(playerSize);
    }
    Camera3D getCamera()
    {
        return camera;
    }

    BoundingBox getTransformedBox()
    {
        matrix = MatrixMultiply(MatrixRotate((Vector3){1,0,0}, 0), MatrixTranslate(camera.position.x+velocity.x, camera.position.y+velocity.z, camera.position.z)); // rotation DOES NOT WORK!

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

    bool collitionCheck(vector<MeshInstance> meshs)
    {
        BoundingBox transformedBox = getTransformedBox();
        for (MeshInstance m : meshs)
        {
            if (CheckCollisionBoxes(transformedBox, m.getBoundingBox()))
            {
                return true;
            }
        }
        return false;
    }
    void process(float dt, vector<MeshInstance> meshs)
    {

        velocity.x = (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) * WALKSPEED * dt -
                     (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) * WALKSPEED * dt;
        velocity.y = (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) * WALKSPEED * dt -
                     (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) * WALKSPEED * dt;
        // velocity.z += 0.0f; // No up-down movement
        // collition check
        Vector3 rotationVelocity = {0,0,0};
        rotationVelocity.x += GetMouseDelta().x * 0.05f;
        rotationVelocity.y += GetMouseDelta().y * 0.05f;

        playerPosition+=velocity;

        BoundingBox transformedBox = getTransformedBox();
        rotation += rotationVelocity;
        DrawBoundingBox(transformedBox,(collitionCheck(meshs) ? RED : GREEN));//
        //if (!collitionCheck(meshs))
        {
            UpdateCameraPro(&camera,
                            velocity,
                            rotationVelocity,
                            0);
                            
        }
        /*else{
            UpdateCameraP
            ro(&camera,
                            (Vector3){0,0,0},
                            rotationVelocity,
                            0);
        }*/
    }
};
#endif