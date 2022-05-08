//
//  GameStatus.cpp
//  Dino Journey
//
//  Created by Nguyễn Tiến Dũng on 4/22/22.
//  Copyright © 2022 Nguyễn Tiến Dũng. All rights reserved.
//

#include "GameStatus.h"
void controlFPS(class ImpTimer& Timer, int FPS)
{
    int real_imp_time = Timer.get_Ticks();
    int time_one_frame = 1000/FPS;
    if (real_imp_time < time_one_frame)
    {
        int delay_time = time_one_frame - real_imp_time;
        SDL_Delay(delay_time);
    }
}
bool checkCollision (class Dino& dino, class Enemy& enemy)
{
    int TRASH_PIXEL_X = 10, TRASH_PIXEL_Y = 10, TRASH_PIXEL_W = 25, TRASH_PIXEL_H = 20;
    
    SDL_Rect d_rect = {dino.getPosX() + TRASH_PIXEL_X, dino.getPosY() + TRASH_PIXEL_Y, dino.getWidth() - TRASH_PIXEL_W, dino.getHeight() - TRASH_PIXEL_H};
    if(enemy.getType() == ON_GROUND_ENEMY)
    {
        TRASH_PIXEL_X = 15, TRASH_PIXEL_Y = 10, TRASH_PIXEL_W = 30, TRASH_PIXEL_H = 0;
    }
    else
    {
        TRASH_PIXEL_X = 15, TRASH_PIXEL_Y = 4, TRASH_PIXEL_W = 15, TRASH_PIXEL_H = 15;
    }
    SDL_Rect e_rect = {enemy.getPosX() + TRASH_PIXEL_X, enemy.getPosY() + TRASH_PIXEL_Y, enemy.getWidth() - TRASH_PIXEL_W, enemy.getHeight() - TRASH_PIXEL_H};

    return SDL_HasIntersection(&d_rect, &e_rect);
}

void drawEndGame(SDL_Renderer* &renderer, bool& play_again, bool& quit_menu, bool& quit_game, int type_map, bool &lose_game)
{
    lose_game = true;
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

    SDL_DestroyTexture(lose_texture);
    SDL_FreeSurface(load_surface);    
    return;
}

void HandlePlayButton(SDL_Event e, BaseObject& gMenu,
                      Button& Play_button,
                      bool& quit_menu,
                      bool& play_again, SDL_Renderer* &renderer,
                      Mix_Chunk *gClickMusic)
{
    if(Play_button.inSide() == true)
    {
        if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            Play_button.status = BUTTON_MOUSE_UP;
            play_again = true; quit_menu = true;
            Mix_PlayChannel(MIX_CHANNEL, gClickMusic, 0);
        }
    }
}

void HandleExitButton(SDL_Event e, BaseObject& gMenu,
                      Button& Exit_button,
                      bool& quit_game, bool& quit_menu,
                      bool& play_again,
                      SDL_Renderer* &renderer,
                      Mix_Chunk *gClickMusic)
{
    if(Exit_button.inSide() == true)
    {
        if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            Exit_button.status = BUTTON_MOUSE_UP;
            play_again = false; quit_game = true; quit_menu = true;
            Mix_PlayChannel(MIX_CHANNEL, gClickMusic, 0);
        }
    }
}
