//
//  Map.cpp
//  Project Game
//
//  Created by Nguyễn Tiến Dũng on 4/23/22.
//  Copyright © 2022 Nguyễn Tiến Dũng. All rights reserved.
//

#include "Map.h"

bool Map::loadBackGround(SDL_Renderer* renderer)
{
    bool success = true;
    for(int i = 0; i < BACKGROUND_LAYER; i++)
    {
        success = backGround[i].loadIMG(bg_layer[i].c_str(), renderer);
        if(success == false) return false ;
    }
    return true;
}

void Map::renderScrollingBackground(SDL_Renderer *renderer)
{
    for(int i = 0; i < BACKGROUND_LAYER; i++)
    {
        backGround[i].setDesRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        backGround[i].Render(renderer);
    }
}

void Map::Free()
{
    Ground.Free();
    for(int i = 0; i < BACKGROUND_LAYER; i++) backGround[i].Free();
}

