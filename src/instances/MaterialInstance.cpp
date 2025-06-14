#include <iostream>
#include <string>
#include "raylib.h"
#include "resource_dir.h"
#include "raymath.h"
#include <cstring>
#include "Instance.cpp"
#ifndef MATERIAL_INSTANCE
#define MATERIAL_INSTANCE

using namespace std;

class MaterialInstance : public Instance
{
private:
    Material material;
    //Texture materialTexture;


public:
    MaterialInstance()
    {
        material = LoadMaterialDefault();
    }

    MaterialInstance(Texture texture/*, string id*/)
    {
        Material m = LoadMaterialDefault();


        //materialTexture = texture;
        SetMaterialTexture(&m, MATERIAL_MAP_DIFFUSE, texture);
        //this->id = id;
        this->material = m;
    }
    Material getMaterial()
    {
        return material;
    }
};
#endif