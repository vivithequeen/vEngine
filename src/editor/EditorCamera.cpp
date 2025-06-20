#include <iostream>
#include <vector>
#include "raylib.h"
#include "rcamera.h"
#include "resource_dir.h"	
#include "raymath.h"

#ifndef EDITOR_CAMERA
#define EDITOR_CAMERA
class EditorCamera{
    public:
    Camera camera;
    EditorCamera(){
        camera = {0};
        

        camera.position = (Vector3){-2.0f, 2.0f, 2.0f};

        camera.target = (Vector3){0.0f, 2.0f, 0.0f};
        camera.up = (Vector3){0.0f, 1.0f, 0.0f};
        camera.fovy = 60.0f;
        camera.projection = CAMERA_PERSPECTIVE;
    }

    int process(float dt, bool move){
        if(move)
        {
            UpdateCamera(&camera, CAMERA_FREE);
        }
        return 0;
    }
};
#endif