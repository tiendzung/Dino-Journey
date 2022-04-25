//
//  Map.cpp
//  Project Game
//
//  Created by Nguyễn Tiến Dũng on 4/23/22.
//  Copyright © 2022 Nguyễn Tiến Dũng. All rights reserved.
//

#include "Map.h"
#include "CommonFunction.h"


bool Map::loadBackGround(SDL_Renderer* renderer, int TOTAL, int type)
{
    bool success = true;
    for(int i = 0; i < TOTAL; i++)
    {
        success = backGround[i].loadIMG(bg_layer[type][i].c_str(), renderer);
        if(success == false)
        {
            return false;
        }
    }
    return true;
}

bool Map::loadGround(SDL_Renderer* renderer, int type)
{
    return Ground.loadIMG(bg_ground[type], renderer);
}
bool Map::loadGrassGround(SDL_Renderer *renderer, int type)
{
    return GrassGround.loadIMG(grass_ground[type], renderer);
}
void Map::renderScrollingBackground(SDL_Renderer *renderer, int TOTAL, vector <double> &bg_speed)
{
//    speed = speed - (BACK_GROUND_SPEED + acceleration);
//    if(speed + backGround[0].getWidth() < 0) speed = 0;
    double k = 1;
    if(type_id == 1) k = 2;
    for(int i = 0; i < TOTAL; i++)
    {
//        backGround[i].setDesRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
//        backGround[i].Render(renderer);
        bg_speed[i] = bg_speed[i] - LAYER_SPEED[i]*k;
        if(bg_speed[i] + backGround[0].getWidth() < 0) bg_speed[i] = 0;
        
        backGround[i].RenderXY(bg_speed[i], SCREEN_HEIGHT - backGround[i].getHeight(), renderer);
        backGround[i].RenderXY(bg_speed[i] + backGround[i].getWidth(), SCREEN_HEIGHT - backGround[i].getHeight(), renderer);
    }
}

void Map::renderScrollingGround(int &speed, int& acceleration, SDL_Renderer* renderer)
{
//    Ground.setDesRect(0, SCREEN_HEIGHT - Ground.getHeight(), Ground.getWidth(), Ground.getHeight());
//
//    Ground.Render(renderer);
    int GROUND_SPEED = 4; /* 4 -> 15*/
    speed = speed - (GROUND_SPEED + acceleration);
    if(speed + Ground.getWidth() < 0) speed = 0;

    Ground.RenderXY(speed, SCREEN_HEIGHT - Ground.getHeight(), renderer);
    Ground.RenderXY(speed + Ground.getWidth(), SCREEN_HEIGHT - Ground.getHeight(), renderer);
}

void Map::renderScrollingGrass(int &speed, int& acceleration, SDL_Renderer* renderer)
{
    speed = speed - (GRASS_GROUND_SPEED + acceleration);
    if(speed + GrassGround.getWidth() < 0) speed = 0;
    
    GrassGround.RenderXY(speed, SCREEN_HEIGHT - GrassGround.getHeight(), renderer);
    GrassGround.RenderXY(speed + GrassGround.getWidth(), SCREEN_HEIGHT - GrassGround.getHeight(), renderer);
}
void Map::Free(int type)
{
    Ground.Free();
    GrassGround.Free();
    for(int i = 0; i < TOTAL_BACKGROUND_LAYER[type]; i++) backGround[i].Free();
}

