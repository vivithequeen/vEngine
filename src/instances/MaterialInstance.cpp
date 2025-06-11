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
        string name;
    public:
        MaterialInstance(){
            material = LoadMaterialDefault();
        }
        MaterialInstance(string filepath, string n){
	        Material m = LoadMaterialDefault();
	        Texture texture;
            char f[filepath.length()+1];
            strcpy(f,filepath.c_str());
	        texture = LoadTexture(f);

	        SetMaterialTexture(&m, MATERIAL_MAP_DIFFUSE, texture);

            this->material = m;
            this->name = n;
        }
        Material getMaterial(){
            return material;
        }

};
#endif
