//
//  Map.cpp
//  Dino Journey
//
//  Created by Nguyễn Tiến Dũng on 4/23/22.
//  Copyright © 2022 Nguyễn Tiến Dũng. All rights reserved.
//

#include "Map.h"
#include "CommonFunction.h"


bool Map::loadBackGround(SDL_Renderer* &renderer, int TOTAL, int type)
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

bool Map::loadGround(SDL_Renderer* &renderer, int type)
{
    return Ground.loadIMG(bg_ground[type], renderer);
}

bool Map::loadGrassGround(SDL_Renderer* &renderer, int type)
{
    return GrassGround.loadIMG(grass_ground[type], renderer);
}

void Map::renderScrollingBackground(SDL_Renderer* &renderer, int TOTAL, vector <double> &bg_pos, int speed, bool move)
{
    for(int i = 0; i < TOTAL; i++)
    {
        if(move == true) bg_pos[i] = bg_pos[i] - (LAYER_SPEED[i] + double((double)speed/(double)2 + 0.5 )); // mấy số magic number đằng sau chỉ là áng chừng, cũng không biết nên đặt tên như nào.
        
        if(bg_pos[i] + backGround[0].getWidth() < 0) bg_pos[i] = 0;
        
        backGround[i].RenderXY(int(bg_pos[i]), SCREEN_HEIGHT - backGround[i].getHeight(), renderer);
        backGround[i].RenderXY(int(bg_pos[i]) + backGround[i].getWidth(), SCREEN_HEIGHT - backGround[i].getHeight(), renderer);
    }
}

void Map::renderScrollingGround(int &pos, int& speed, SDL_Renderer* &renderer, bool move)
{
    if(move == true) pos = pos - (GROUND_SPEED + speed);
    if(pos + Ground.getWidth() < 0) pos = 0;

    Ground.RenderXY(pos, SCREEN_HEIGHT - Ground.getHeight(), renderer);
    Ground.RenderXY(pos + Ground.getWidth(), SCREEN_HEIGHT - Ground.getHeight(), renderer);
}

void Map::renderScrollingGrass(int &pos, int& speed, SDL_Renderer* &renderer, bool move)
{
    if(move == true) pos = pos - (GRASS_GROUND_SPEED + speed);
    if(pos + GrassGround.getWidth() < 0) pos = 0;
    
    GrassGround.RenderXY(pos, SCREEN_HEIGHT - GrassGround.getHeight(), renderer);
    GrassGround.RenderXY(pos + GrassGround.getWidth(), SCREEN_HEIGHT - GrassGround.getHeight(), renderer);
}

void Map::Free(int type)
{
    Ground.Free();
    GrassGround.Free();
    for(int i = 0; i < TOTAL_BACKGROUND_LAYER[type]; i++) backGround[i].Free();
}

