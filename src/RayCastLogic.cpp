#include <iostream>
#include <math.h>
#include "raylib.h"
#include "resource_dir.h"	
#include "Map.cpp"
#include <fstream>
using namespace std;

class RayCastLogic{
    public:
        float playerx, playery, playerrotation;
        int playerfov;

        Map map;
        RayCastLogic()
        {

        }

        RayCastLogic(float x, float y, int fov)
        {
            angles = new float[GetScreenWidth()];
            this -> playerx = x;
            this -> playery = y;
            this -> playerfov = fov;
            playerrotation = 0;
            initializeRotations();
        }



        void initializeRotations(){
            float step = (tan((playerfov / 2)*DEG2RAD) * 2) / (GetScreenWidth()-1);
  
            for(int i = 0; i < GetScreenWidth(); i++){
                float pos = (-1 + i*step);
                angles[i] = atan(pos);

            }
        }

        bool raycast(float angle, float ix, float iy,int index, float beta){
            float initx = ix;
            float inity = iy;
            
            float x = initx;
            float y = inity;
            
            float scale = 0.005;

            float dx = cos(angle);
            float dy = sin(angle);

            int rayindex = 0;
            while (map.currentMap[(int)(y)][(int)(x)] == 0)
            {
                x+=dx * scale;
                y+=dy * scale;
                if(rayindex > 10000){
                    return false;
                }
                rayindex++;
            }
            float fx = initx - x;
            float fy = inity - y;
            float distance = sqrt(fx*fx+fy*fy) * cos(beta);
            
            int height = ((1080)/(distance));
            height=max(min(height,1080*32),1);



            int offset = (1080/2) - (height / 2);
            DrawRectangle(index, offset, 1, height, BLUE);
            return true;
        }


        void renderWalls()
        {
            for(int i = 0; i < GetScreenWidth();i++){
                raycast(angles[i] + playerrotation * DEG2RAD, playerx,playery,i,angles[i]);
            }
        }

        float getAngle(int index){
            return angles[index];
        }
        
        void handleInputs(float dt){
            if(IsKeyDown(KEY_A)){
                playerx+=cos(playerrotation*DEG2RAD - PI/2)* dt;
                playery+=sin(playerrotation*DEG2RAD - PI/2)* dt;
            }
            if(IsKeyDown(KEY_D)){
                playerx+=cos(playerrotation*DEG2RAD + PI/2)* dt;
                playery+=sin(playerrotation*DEG2RAD + PI/2)* dt;
            }
            if(IsKeyDown(KEY_W)){
                playerx+=cos(playerrotation*DEG2RAD)* dt;
                playery+=sin(playerrotation*DEG2RAD)* dt;
            }
            if(IsKeyDown(KEY_S)){
                playerx-=cos(playerrotation*DEG2RAD) * dt;
                playery-=sin(playerrotation*DEG2RAD) * dt;
            }
            playerrotation+= dt * 10 * GetMouseDelta().x;
        }

        void process(float dt){
            handleInputs(dt);
            renderWalls();
            
        }

    private:
        float* angles;
};