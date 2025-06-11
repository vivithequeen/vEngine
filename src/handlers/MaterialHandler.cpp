#include <iostream>
#include <vector>
#include "raylib.h"

#include "resource_dir.h"	
#include "raymath.h"

#include "../instances/MaterialInstance.cpp"
class MaterialHandler{
    private:
    std::vector<MaterialInstance> materials;
    public:
    MaterialHandler(){

    }
    int addMaterial(MaterialInstance materialInstance){
        materials.push_back(materialInstance);
    }

    MaterialInstance getMaterialByIndex(int index){
        return materials.at(index);
    }

};