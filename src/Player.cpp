#include <iostream>
#include "raylib.h"
#include "rcamera.h"
#include "resource_dir.h"

using namespace std;

class Player
{
public:
    Camera3D camera;
    const float WALKSPEED = 7.0f;

    Vector3 velocity = {0,0,0};
    float playerHeight = 2;
    Player()
    {
        camera = {0};
        camera.position = (Vector3){0.0f, 2.0f, 2.0f};
        camera.target = (Vector3){0.0f, 2.0f, 0.0f};
        camera.up = (Vector3){0.0f, 1.0f, 0.0f};
        camera.fovy = 60.0f;
        camera.projection = CAMERA_PERSPECTIVE;
    }

    void process(float dt)
    { 
        velocity.x = (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) * WALKSPEED*dt -
                      (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) * WALKSPEED*dt;
        velocity.y = (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) * WALKSPEED*dt -
                      (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) * WALKSPEED*dt;
        // velocity.z += 0.0f; // No up-down movement

        UpdateCameraPro(&camera,
                        velocity,
                        (Vector3){
                            GetMouseDelta().x * 0.05f, // Rotation: yaw
                            GetMouseDelta().y * 0.05f, // Rotation: pitch
                            0.0f                       // Rotation: roll
                        },
                        0);
    }
};