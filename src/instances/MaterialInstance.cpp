#include <iostream>
#include "raylib.h"
#include "resource_dir.h"
#include "raymath.h"
using namespace std;

class MaterialInstance{
    private:
        Material material;
        string name;
    public:
        MaterialInstance();
        MaterialInstance(Material material, string name){
            this->material = material;
            this->name = name;
        }
};