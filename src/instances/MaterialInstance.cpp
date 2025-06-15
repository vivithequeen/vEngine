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
    Texture materialTexture;
    string filepath;

public:
    MaterialInstance()
    {
        material = LoadMaterialDefault();
    }

    MaterialInstance(string initfilepath/*, string id*/)
    {
        Material m = LoadMaterialDefault();
        this->filepath = initfilepath;
        
        char f[filepath.length() + 1];
        strcpy(f, filepath.c_str());
        materialTexture = LoadTexture(f);


        SetMaterialTexture(&m, MATERIAL_MAP_DIFFUSE, materialTexture);
        //this->id = id;
        this->name = "MaterialInstance";
        this->material = m;
    }
    int getEditorOptions() override
    {
        Instance::getEditorOptions();
        ImGui::SeparatorText("Material Instance");
        

        rlImGuiImage(&materialTexture);
        ImGui::Text("Texture Resolution: %d x %d", materialTexture.width,materialTexture.height);
        ImGui::Text("Texture Filepath: %s", filepath.c_str());

        //do stuff here
        return 0;
    }
    Material getMaterial()
    {
        return material;
    }
};
#endif