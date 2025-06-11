#include <iostream>
#include <vector>
#include "raylib.h"

#include "resource_dir.h"	
#include "raymath.h"

#include "../instances/MaterialInstance.cpp"

using namespace std;
class MaterialHandler{
    private:
    vector<MaterialInstance> materials;
    public:
    MaterialHandler(){

    }
    int addMaterial(MaterialInstance materialInstance){

        
        materials.push_back(materialInstance);
        return 0;
    }

    MaterialInstance getMaterialByIndex(int index){
        return materials.at(index);
    }

};