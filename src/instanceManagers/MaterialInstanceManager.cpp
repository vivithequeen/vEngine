#include <iostream>
#include <vector>
#include "raylib.h"

#include "resource_dir.h"
#include "raymath.h"

#include "../instances/MaterialInstance.cpp"

using namespace std;
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