#include <iostream>
#include <math.h>
#include "raylib.h"
#include "resource_dir.h"	
#include <fstream>
using namespace std;

class RayCastLogic{
    public:
        float playerx, playery, playerrotation;
        int playerfov;


        RayCastLogic(float x, float y, int fov)
        {
            angles = new float[GetScreenWidth()];
            this -> playerx = x;
            this -> playery = y;
            this -> playerfov = fov;
            initializeRotations();
        }



        void initializeRotations(){
            float step = (tan(playerfov / 2) * 2) / GetScreenWidth();
  
            for(int i = 0; i < GetScreenWidth(); i++){
                float pos = (-1 + i*step);
                angles[i] = atan(pos);


            }

        }
        
        float getAngle(int index){
            return angles[index];
        }

    private:
        float* angles;
};