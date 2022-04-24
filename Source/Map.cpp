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

void Map::renderScrollingBackground(SDL_Renderer *renderer, int TOTAL)
{
    for(int i = 0; i < TOTAL; i++)
    {
        backGround[i].setDesRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        backGround[i].Render(renderer);
    }
}

void Map::renderScrollingGround(int &speed, int& acceleration, SDL_Renderer* renderer)
{
//    Ground.setDesRect(0, SCREEN_HEIGHT - Ground.getHeight(), Ground.getWidth(), Ground.getHeight());
//
//    Ground.Render(renderer);
    speed = speed - (GROUND_SPEED + acceleration);
    if(speed < - Ground.getWidth())
        speed = 0;

    Ground.RenderXY(speed, SCREEN_HEIGHT - Ground.getHeight(), renderer);
    Ground.RenderXY(speed + Ground.getWidth(), SCREEN_HEIGHT - Ground.getHeight(), renderer);
}

void Map::Free(int type)
{
    Ground.Free();
    for(int i = 0; i < TOTAL_BACKGROUND_LAYER[type]; i++) backGround[i].Free();
}

