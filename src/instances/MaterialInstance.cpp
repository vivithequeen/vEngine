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
        

        materialTexture = LoadTexture(filepath.c_str());


        SetMaterialTexture(&m, MATERIAL_MAP_DIFFUSE, materialTexture);
        //this->id = id;
        this->name = "MaterialInstance";
        this->material = m;
    }
    int updateTexture()
    {


        materialTexture = LoadTexture(filepath.c_str());


        SetMaterialTexture(&material, MATERIAL_MAP_DIFFUSE, materialTexture);

        return 0;
    }
    int getEditorOptions() override
    {
        Instance::getEditorOptions();
        ImGui::SeparatorText("Material Instance");
        

        rlImGuiImageSize(&materialTexture,100,100);
        ImGui::Text("Texture Resolution: %d x %d", materialTexture.width,materialTexture.height);
        ImGui::Text("Texture Filepath: %s", filepath.c_str());
        ImGui::Button("Upload Image");
        if(ImGui::BeginDragDropTarget()){
            if(const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("FILEPATH")){
                std::string newFilePath((const char*)payload->Data, payload->DataSize - 1); 
                newFilePath = newFilePath.substr(13);
                if(newFilePath.substr(newFilePath.size()-3,newFilePath.size()) == "png")
                {
                    filepath = newFilePath;
                    updateTexture();
                }
                
            }
        }
        //do stuff here
        return 0;
    }

    Material getMaterial()
    {
        return material;
    }
};
#endif