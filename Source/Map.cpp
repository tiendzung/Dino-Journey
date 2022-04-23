//
//  Map.cpp
//  Project Game
//
//  Created by Nguyễn Tiến Dũng on 4/23/22.
//  Copyright © 2022 Nguyễn Tiến Dũng. All rights reserved.
//

#include "Map.h"

bool Map::loadBackGround(SDL_Renderer* renderer, int TOTAL)
{
    bool success = true;
    for(int i = 0; i < TOTAL; i++)
    {
        success = backGround[i].loadIMG(bg_1_layer[i].c_str(), renderer);
        if(success == false) return false ;
    }
    return true;
}

bool Map::loadGround(string path, SDL_Renderer* renderer)
{
    return Ground.loadIMG(path.c_str(), renderer);
}

void Map::renderScrollingBackground(SDL_Renderer *renderer, int TOTAL)
{
    for(int i = 0; i < TOTAL; i++)
    {
        backGround[i].setDesRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        backGround[i].Render(renderer);
    }
}

void Map::renderScrollingGround(/*int &speed, int& acceleration,*/ SDL_Renderer* renderer)
{
    Ground.setDesRect(0, SCREEN_HEIGHT - Ground.getHeight(), Ground.getWidth(), Ground.getHeight());
    Ground.Render(renderer);
}

void Map::Free()
{
    Ground.Free();
    for(int i = 0; i < BACKGROUND_LAYER_1; i++) backGround[i].Free();
}

