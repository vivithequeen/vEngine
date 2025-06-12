#include <iostream>
#include <vector>
#include "raylib.h"
#include "rcamera.h"
#include "resource_dir.h"	
#include "raymath.h"

#include "EditorCamera.cpp"

class Editor
{
    public:

    EditorCamera editorCamera;

    Editor(){

    }

    int process(float dt){
        editorCamera.process(dt);
        return 0;
    }
};