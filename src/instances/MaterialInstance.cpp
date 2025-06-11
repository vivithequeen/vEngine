#include <iostream>
#include <string>
#include "raylib.h"
#include "resource_dir.h"
#include "raymath.h"
#include <cstring> 

#ifndef MATERIAL_INSTANCE
#define MATERIAL_INSTANCE

using namespace std;



class MaterialInstance
{
    private:
        Material material;
        Texture materialTexture;
        string name;
    public:
        MaterialInstance(){
            material = LoadMaterialDefault();
        }
        MaterialInstance(string filepath, string n){
	        Material m = LoadMaterialDefault();

            char f[filepath.length()+1];
            strcpy(f,filepath.c_str());
	        materialTexture = LoadTexture(f);

	        SetMaterialTexture(&m, MATERIAL_MAP_DIFFUSE, materialTexture);

            this->material = m;
            this->name = n;
        }
        Material getMaterial(){
            return material;
        }

};
#endif