//
//  GameStatus.cpp
//  Project Game
//
//  Created by Nguyễn Tiến Dũng on 4/22/22.
//  Copyright © 2022 Nguyễn Tiến Dũng. All rights reserved.
//

#include "GameStatus.h"

bool checkCollision (class Dino& dino, class Enemy& enemy)
{
    int TRASH_PIXEL_X = 10, TRASH_PIXEL_Y = 10, TRASH_PIXEL_W = 25, TRASH_PIXEL_H = 20;
    
    SDL_Rect d_rect = {dino.getPosX() + TRASH_PIXEL_X, dino.getPosY() + TRASH_PIXEL_Y, dino.getWidth() - TRASH_PIXEL_W, dino.getHeight() - TRASH_PIXEL_H};
    if(enemy.getType() == ON_GROUND_ENEMY)
    {
        TRASH_PIXEL_X = 15, TRASH_PIXEL_Y = 5, TRASH_PIXEL_W = 30, TRASH_PIXEL_H = 0;
    }
    else
    {
        TRASH_PIXEL_X = 15, TRASH_PIXEL_Y = 4, TRASH_PIXEL_W = 15, TRASH_PIXEL_H = 15;
    }
    SDL_Rect e_rect = {enemy.getX() + TRASH_PIXEL_X, enemy.getY() + TRASH_PIXEL_Y, enemy.getW() - TRASH_PIXEL_W, enemy.getH() - TRASH_PIXEL_H};

    return SDL_HasIntersection(&d_rect, &e_rect);
}

void drawEndGame(SDL_Renderer* renderer, bool& play_again, bool& quit_game, int type_map)
{
    string path;
    switch(type_map)
    {
        case FOREST: { path = "Resource/Menu/LooseScreenWhite.png"; break; }
        case HILLS: { path = "Resource/Menu/LooseScreenBlack.png"; break; }
        case CLOUD_MOUTAIN: { path = "Resource/Menu/LooseScreenBlack.png"; break; }
        case NIGHT_CITY: { path = "Resource/Menu/LooseScreenBlack.png"; break; }
        case DESERT: { path = "Resource/Menu/LooseScreenBlack.png"; break; }
        case FAR_CITY: { path = "Resource/Menu/LooseScreenBlack.png"; break; }
    }
    SDL_Surface* load_surface = IMG_Load(path.c_str());
    SDL_Texture* lose_texture = SDL_CreateTextureFromSurface(renderer, load_surface);
    SDL_RenderCopy(renderer, lose_texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    
    SDL_DestroyTexture(lose_texture);
    SDL_FreeSurface(load_surface);
    bool end_game = false;
    while(!end_game)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                play_again = false;
                return;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_SPACE:
                        end_game = true;
                        return;
                        
                    case SDLK_ESCAPE:
                        end_game = true;
                        play_again = false;
                        quit_game = false;
                        return;
                }
            }
        }
    }
    return;
}
