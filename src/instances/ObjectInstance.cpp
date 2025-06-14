#include <iostream>
#include "raylib.h"
#include "resource_dir.h"
#include "raymath.h"
#include "MaterialInstance.cpp"
using namespace std;
#ifndef OBJECT_INSTANCE
#define OBJECT_INSTANCE
class ObjectInstance{
    public:

    Vector3 position;
    Vector3 rotation;

    ObjectInstance(){
        
    }
};
#endif
