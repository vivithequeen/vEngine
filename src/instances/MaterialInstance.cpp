#include <iostream>
#include <string>
#include "raylib.h"
#include "resource_dir.h"
#include "raymath.h"
#include <cstring> 
using namespace std;


class MaterialInstance{
    private:
        Material material;
        string name;
    public:
        MaterialInstance();
        MaterialInstance(string filepath, string name){
	        Material material = LoadMaterialDefault();
	        Texture texture;
            char f[filepath.length()+1];
            strcpy(f,filepath.c_str());
	        texture = LoadTexture(f);

	        SetMaterialTexture(&material, MATERIAL_MAP_DIFFUSE, texture);

            this->material = material;
            this->name = name;
        }

};

