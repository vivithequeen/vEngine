#include <iostream>
#include <vector>
#include "raylib.h"
#include "rcamera.h"
#include "resource_dir.h"	
#include "raymath.h"
#include "imgui.h"
#include "rlImGui.h"

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
        
    public:
        int gameMode;
    	InstanceManager instanceManager;
    	Editor editor;
        PlayerInstance player;
        
    GameWorld()
    {
        gameMode = EDIT;
    }


    Camera getCurrentCamera()
    {
        if(gameMode == EDIT){
            return editor.editorCamera.camera;
        }
        if(gameMode == GAME){
            return player.getCamera();
        }
        return Camera();
    }

    int draw3D(){
        if(gameMode == EDIT)
        {
		    editor.process(GetFrameTime());
        }
        if(gameMode == GAME){
            //player.process(GetFrameTime(),instanceManager.meshInstanceManager.getMeshs());
        }
		DrawGrid(17,1);

		instanceManager.process(GetFrameTime());



        return 0;
    }

    int draw2D(RenderTexture2D renderTexture){
        //DrawFPS(0,0);

        editor.draw2D(renderTexture,instanceManager);


        return 0;
    }

};