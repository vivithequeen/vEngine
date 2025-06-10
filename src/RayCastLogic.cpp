#include <iostream>
#include <math.h>
#include "raylib.h"
#include "resource_dir.h"
#include "Map.cpp"
#include <fstream>
using namespace std;

class RayCastLogic
{
public:
    float playerx, playery, playerrotation;
    int playerfov;

    Map map;
    RayCastLogic()
    {

    }

    RayCastLogic(float x, float y, int fov)
    {
        textures[1] = LoadTexture("testMeow.png");
        angles = new float[GetScreenWidth()];
        this->playerx = x;
        this->playery = y;
        this->playerfov = fov;
        playerrotation = 0;
        initializeRotations();
    }

    void initializeRotations()
    {
        float step = (tan((playerfov / 2) * DEG2RAD) * 2) / (GetScreenWidth() - 1);

        for (int i = 0; i < GetScreenWidth(); i++)
        {
            float pos = (-1 + i * step);
            angles[i] = atan(pos);
        }
    }

    int drawColumn(int step, int height, int offset, float x, float y, int tileValue)
    {

        float axis = floor((x-(int)(x)) * 100) >1 ? x : y; // does not fully work yet

        int column = floor((axis - (int)(axis)) * 100);

        DrawTexturePro(textures[tileValue], {column * 1.0f, 0, 1, 100}, {step * 1.0f, offset * 1.0f, 1, height * 1.0f}, {0, 0}, 0, getDarkness(height));

        return 0;
        }

    int drawFloor(int step, int height, int offset, float x, float y)
    {
        return 0;
    }

    Color getDarkness(float height){
        float d = height * 255.0f/GetScreenHeight();
        d = min(d,255.0f);
        Color c =  {d,d,d,255};
        return c;
    }

    bool raycast(float angle, float ix, float iy, int step, float beta)
    {
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
            x += dx * scale;
            y += dy * scale;
            if (rayindex > 10000)
            {
                return false;
            }
            rayindex++;
        }

        int tileValue = map.currentMap[(int)(y)][(int)(x)];
        float fx = initx - x;
        float fy = inity - y;
        float distance = sqrt(fx * fx + fy * fy) * cos(beta);

        int height = ((1080) / (distance));
        height = max(min(height, 1080 * 32), 1);

        int offset = (1080 / 2) - (height / 2);
        // DrawRectangle(step, offset, 1, height, BLUE);
        drawColumn(step, height, offset, x, y, tileValue);
        drawFloor(step,height,offset,x,y);
        return true;
    }

    void renderWalls()
    {
        for (int i = 0; i < GetScreenWidth(); i++)
        {
            raycast(angles[i] + playerrotation * DEG2RAD, playerx, playery, i, angles[i]);
        }
    }

    float getAngle(int index)
    {
        return angles[index];
    }

    bool checkCollition(float x, float y)
    {
        return map.currentMap[(int)y][(int)x] == 0;
    }
    void handleInputs(float dt)
    {
        if (IsKeyDown(KEY_A))
        {
            if (checkCollition(playerx + cos(playerrotation * DEG2RAD - PI / 2) * dt, playery + sin(playerrotation * DEG2RAD - PI / 2) * dt))
            {
                playerx += cos(playerrotation * DEG2RAD - PI / 2) * dt;
                playery += sin(playerrotation * DEG2RAD - PI / 2) * dt;
            }
        }
        if (IsKeyDown(KEY_D))
        {
            if (checkCollition(playerx + cos(playerrotation * DEG2RAD + PI / 2) * dt, playery + sin(playerrotation * DEG2RAD + PI / 2) * dt))
            {
                playerx += cos(playerrotation * DEG2RAD + PI / 2) * dt;
                playery += sin(playerrotation * DEG2RAD + PI / 2) * dt;
            }
        }
        if (IsKeyDown(KEY_W))
        {
            if (checkCollition(playerx + cos(playerrotation * DEG2RAD) * dt, playery + sin(playerrotation * DEG2RAD) * dt))
            {
                playerx += cos(playerrotation * DEG2RAD) * dt;
                playery += sin(playerrotation * DEG2RAD) * dt;
            }
        }
        if (IsKeyDown(KEY_S))
        {
            if (checkCollition(playerx - cos(playerrotation * DEG2RAD) * dt, playery - sin(playerrotation * DEG2RAD) * dt))
            {
                playerx -= cos(playerrotation * DEG2RAD) * dt;
                playery -= sin(playerrotation * DEG2RAD) * dt;
            }
        }
        playerrotation += dt * 10 * GetMouseDelta().x;
    }
    void exit(){
        for(Texture2D t : textures)
        {
            UnloadTexture(t);
        }
    }
    void process(float dt)
    {
        handleInputs(dt);
        renderWalls();
    }

private:
    float *angles;
    Texture2D textures[16];
};