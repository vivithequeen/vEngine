#include <iostream>
#include <vector>
#include "raylib.h"
#include "rcamera.h"
#include "resource_dir.h"	
#include "raymath.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "instanceManagers/InstanceManager.cpp"
#include "editor/Editor.cpp"
#include "instances/PlayerInstance.cpp"

enum { // mode
    EDIT = 0,
    GAME = 1,
};

class GameWorld
{
    private:
        int gameMode = GAME;
    public:
    	InstanceManager instanceManager;
    	Editor editor;
        PlayerInstance player;
        
    GameWorld()
    {

    }


    Camera getCurrentCamera()
    {
        if(gameMode = EDIT){
            return editor.editorCamera.camera;
        }
        if(gameMode = GAME){
            return player.getCamera();
        }
    }

    int draw3D(){
        if(gameMode == EDIT)
        {
		    editor.process(GetFrameTime());
        }
        if(gameMode == GAME){
            player.process(GetFrameTime(),instanceManager.meshInstanceManager.getMeshs());
        }
		DrawGrid(17,1);

		instanceManager.process(GetFrameTime());



        return 0;
    }

    int draw2D(){
        DrawFPS(0,0);


        return 0;
    }

};