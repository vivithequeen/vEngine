#include <iostream>
#include <vector>
#include "raylib.h"

#include "resource_dir.h"
#include "raymath.h"

#include "../instances/MaterialInstance.cpp"

using namespace std;
#ifndef MATERIAL_INSTANCE_MANAGER
#define MATERIAL_INSTANCE_MANAGER
class MaterialInstanceManager
{
private:
    vector<MaterialInstance> materials;

public:
    MaterialInstanceManager()
    {
        
    }
    int addMaterial(MaterialInstance materialInstance)
    {

        materials.push_back(materialInstance);
        return 0;
    }

    MaterialInstance getMaterialByIndex(int index)
    {
        return materials.at(index);
    }
};
#endif