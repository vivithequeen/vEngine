#include <iostream>
#include <vector>

#include "raylib.h"
#include "resource_dir.h"
#include <cstring>

using namespace std;

class TextureInstanceManager
{
    private:

    vector<Texture> textures= {};

    public:
    TextureInstanceManager(){
        
    }

    int addTextureFromPath(string filepath){
        Texture t;
        char f[filepath.length() + 1];
        strcpy(f, filepath.c_str());
        t = LoadTexture(f);

        textures.push_back(t);
        return 0;

    }
	Texture getTextureByIndex(int index)
	{
		return textures.at(index);
	}

};